// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.


#include "Actors/Gameplay/HYWaveManager.h"
#include "Characters/HYEnemyBase.h"
#include "Health/HYHealthComponent.h"
#include "HYFunctionLibrary.h"

// Sets default values
AHYWaveManager::AHYWaveManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AHYWaveManager::StartWave()
{
	if (bIsWaveActive)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tried to start wave while previous wasn't finished!"));
		return;
	}

	ClearEnemies();

	FTimerManagerTimerParameters TimerParams;
	TimerParams.bLoop = false;

	GetWorld()->GetTimerManager().SetTimer(WaveTimerHandle, this, &AHYWaveManager::EndWave, WaveLength, TimerParams);

	TimerParams.bLoop = true;
	GetWorld()->GetTimerManager().SetTimer(SpawnerTimerHandle, this, &AHYWaveManager::TrySpawnEnemy, SpawnCheckFrequency, TimerParams);

	bIsWaveActive = true;

	TrySpawnEnemy();

	CurrentWave++;
	OnWaveStarted.Broadcast();
}

void AHYWaveManager::EndWave()
{
	EndWaveWithResult(true);
}

void AHYWaveManager::EndWaveWithResult(bool bWasSuccessful)
{
	if (!bIsWaveActive)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tried to end inactive wave!"));
		return;
	}

	// Stop spawning new enemies
	GetWorld()->GetTimerManager().ClearTimer(SpawnerTimerHandle);
	
	if (bWasSuccessful)
	{
		ClearEnemies();
	}

	bIsWaveActive = false;
	OnWaveEnded.Broadcast(bWasSuccessful);
}

void AHYWaveManager::ResetWaves()
{
	CurrentWave = 0;
}

void AHYWaveManager::TrySpawnEnemy()
{
	if (!bIsWaveActive)
	{
		return;
	}

	// Determine if we should spawn an enemy backstage
	ESpawnType NewSpawnType = FMath::RandRange(0.0f, 1.0f) > BackstageSpawnChance ? ESpawnType::Entrance : ESpawnType::Backstage;
	FGameplayTag EnemyType = NewSpawnType == ESpawnType::Backstage ? TAG_Enemy_Type_Backstage : TAG_Enemy_Type_Entrance;

	if (!CanSpawnType(EnemyType))
	{
		return;
	}

	if (SpawnPoints.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("No Spawn Points specified for %s!"), *GetNameSafe(this));
		return;
	}


	int32 SpawnPointIndex = FMath::RandRange(0, GetSpawnPoints(NewSpawnType).Num() - 1);
	FTransform SpawnTransform = GetSpawnPoints(NewSpawnType)[SpawnPointIndex]->GetActorTransform();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	FGameplayTag RandomizedType = UHYFunctionLibrary::GetRandomTag(UHYFunctionLibrary::GetGameplayTagLastChildrenOnly(EnemyType));

	FHYEnemyDescription EnemyDescription = 
		UHYFunctionLibrary::GetDescriptionFromEnemyType(RandomizedType);

	if (AHYEnemyBase* SpawnedEnemy = UHYFunctionLibrary::SpawnEnemyFromDescription(EnemyDescription, SpawnTransform))
	{
		SpawnedEnemy->SetType(EnemyType);

		SpawnedEnemy->GetHealthComponent()->OnDeath.AddDynamic(this, &AHYWaveManager::HandleDeadEnemy);	
		SpawnedEnemies.Add(SpawnedEnemy);

		if (!SpawnedEnemiesCount.Contains(EnemyType))
		{
			SpawnedEnemiesCount.Add(EnemyType, 0);
		}

		SpawnedEnemiesCount[EnemyType] += 1;

		OnEnemySpawned.Broadcast(SpawnedEnemy, NewSpawnType);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't spawn enemy at spawn point %d"), SpawnPointIndex);
		return;
	}
}

void AHYWaveManager::HandleDeadEnemy(FHYDamageInfo LethalDamageInfo)
{
	if (!LethalDamageInfo.IsValidDamageInfo())
	{
		return;
	}

	AHYEnemyBase* DeadEnemy = Cast<AHYEnemyBase>(LethalDamageInfo.GetTarget());

	if (!IsValid(DeadEnemy))
	{
		for (auto It = SpawnedEnemies.CreateIterator(); It; ++It)
		{
			if (!IsValid(*It))
			{
				It.RemoveCurrent();
			}
		}
	}
	else
	{
		SpawnedEnemies.Remove(DeadEnemy);
		SpawnedEnemiesCount[DeadEnemy->GetType()] -= 1;
	}
}

bool AHYWaveManager::CanSpawnType(const FGameplayTag& Type)
{
	return SpawnedEnemiesCount.Contains(Type) ? (SpawnedEnemiesCount[Type] < EnemyLimit[Type]) : true;
}

// Called when the game starts or when spawned
void AHYWaveManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHYWaveManager::ClearEnemies()
{
	// Kill all enemies after wave ends
	for (AHYEnemyBase* Enemy : SpawnedEnemies)
	{
		if (!IsValid(Enemy))
		{
			continue;
		}

		Enemy->GetHealthComponent()->OverrideHealth(0.0f);
	}

	SpawnedEnemiesCount.Empty();
	SpawnedEnemies.Empty();
}

// Called every frame
void AHYWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

