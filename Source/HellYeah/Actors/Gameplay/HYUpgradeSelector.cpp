// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Gameplay/HYUpgradeSelector.h"
#include "HYGameplayTags.h"
#include "GameplayTagsManager.h"
#include "Actors/Gameplay/HYUpgradeItem.h"
#include "Components/HYGrabComponent.h"
#include "Components/HYMotionControllerComponent.h"

// Sets default values
AHYUpgradeSelector::AHYUpgradeSelector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AHYUpgradeSelector::StartUpgradeSelection()
{
	const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	FGameplayTagContainer UpgradeContainer = Manager.RequestGameplayTagChildren(TAG_Upgrade.GetTag());
	
	TSet<FGameplayTag> RandomTags;

	while (RandomTags.Num() != ItemsAmount)
	{
		RandomTags.Add(UpgradeContainer.GetByIndex(FMath::RandRange(0, UpgradeContainer.Num() - 1)));
	}

	// Row layout settings
	const FVector Origin = GetActorLocation();

	const int32 TotalItems = RandomTags.Num();
	float StartX = -((TotalItems - 1) * 0.5f) * ItemSpacing;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	int32 Index = 0;
	for (const FGameplayTag& Tag : RandomTags)
	{
		const FVector SpawnLocation = Origin + GetActorRightVector() * (StartX + Index * ItemSpacing);
		if (AHYUpgradeItem* Item = GetWorld()->SpawnActor<AHYUpgradeItem>(ItemClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams))
		{
			Item->SetUpgradeTag(Tag);
			Item->OnUpgradeItemGrabbed.AddDynamic(this, &AHYUpgradeSelector::FinishUpgradeSelection);
			UpgradeItems.Add(Item);
		}

		Index++;
	}

	OnUpgradeSelectionStarted.Broadcast();
}

void AHYUpgradeSelector::FinishUpgradeSelection(AHYUpgradeItem* UpgradeItem)
{
	OnUpgradeSelected.Broadcast(UpgradeItem->GetUpgradeTag());

	for (AHYUpgradeItem* Item : UpgradeItems)
	{
		Item->Destroy();
	}

	UpgradeItems.Empty();
}

// Called when the game starts or when spawned
void AHYUpgradeSelector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHYUpgradeSelector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

