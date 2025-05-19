// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HYWaveManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWaveStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveEnded, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemySpawned, AHYEnemyBase*, SpawnedEnemy);

class AHYEnemyBase;
struct FHYDamageInfo;

UCLASS()
class HELLYEAH_API AHYWaveManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHYWaveManager();

	UPROPERTY(BlueprintAssignable)
	FOnWaveStarted OnWaveStarted;

	UPROPERTY(BlueprintAssignable)
	FOnWaveEnded OnWaveEnded;

	UPROPERTY(BlueprintAssignable)
	FOnEnemySpawned OnEnemySpawned;

	UFUNCTION(BlueprintCallable)
	void StartWave();

	// Called by the timer (defaults to success)
	UFUNCTION()
	void EndWave();

	// Called manually to control wave outcome (true = success, false = failure)
	UFUNCTION(BlueprintCallable)
	void EndWaveWithResult(bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
	void ResetWaves();

	UFUNCTION(BlueprintCallable)
	void TrySpawnEnemy();

	UFUNCTION(BlueprintCallable)
	void HandleDeadEnemy(FHYDamageInfo LethalDamageInfo);

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentWave() const { return CurrentWave; }

	UFUNCTION(BlueprintCallable)
	bool IsWaveActive() const { return bIsWaveActive; }

	UFUNCTION(BlueprintCallable)
	FTimerHandle GetWaveTimer() const { return WaveTimerHandle; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn = true))
	TArray<TObjectPtr<AActor>> SpawnPoints;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// ======= Waves ===========

	UPROPERTY(BlueprintReadOnly)
	bool bIsWaveActive = false;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentWave = 0;

	// Wave length in seconds
	UPROPERTY(BlueprintReadOnly)
	float WaveLength = 60.0f;

	UPROPERTY()
	FTimerHandle WaveTimerHandle;

	// ========== Spawning ==========

	UPROPERTY()
	FTimerHandle SpawnerTimerHandle;

	// Frequency of enemy spawn checks
	UPROPERTY(BlueprintReadOnly)
	float SpawnCheckFrequency = 2.5f;

	UPROPERTY(BlueprintReadOnly)
	int32 EnemyLimit = 10;

	UPROPERTY()
	TSet<TObjectPtr<AHYEnemyBase>> SpawnedEnemies;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<AHYEnemyBase> EnemyClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
