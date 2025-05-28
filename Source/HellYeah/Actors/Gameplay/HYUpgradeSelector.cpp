// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.


#include "Actors/Gameplay/HYUpgradeSelector.h"
#include "HYGameplayTags.h"
#include "GameplayTagsManager.h"
#include "Actors/Gameplay/HYUpgradeItem.h"
#include "Components/HYGrabComponent.h"
#include "Components/HYMotionControllerComponent.h"
#include "HYFunctionLibrary.h"

// Sets default values
AHYUpgradeSelector::AHYUpgradeSelector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AHYUpgradeSelector::StartUpgradeSelection()
{
	const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	FGameplayTagContainer UpgradeContainer = UHYFunctionLibrary::GetGameplayTagLastChildrenOnly(TAG_Upgrade.GetTag());
	FGameplayTagContainer FilteredContainer = UHYFunctionLibrary::FilterContainer(UpgradeContainer, ExcludeTags);

	TSet<FGameplayTag> RandomTags;
	
	for (int32 i = 0; i < ItemsAmount; i++)
	{
		FGameplayTag Tag = UHYFunctionLibrary::GetRandomTag(FilteredContainer);
		
		RandomTags.Add(Tag);
		FilteredContainer.RemoveTag(Tag);
	}

	// Row layout settings
	const FVector Origin = GetActorLocation();
	const FVector LookAtPoint = GetActorLocation() + (GetActorForwardVector() * CurveOffset);
	
	const int32 TotalItems = RandomTags.Num();
	float StartX = -((TotalItems - 1) * 0.5f) * ItemSpacing;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	int32 Index = 0;
	for (const FGameplayTag& Tag : RandomTags)
	{
		const FVector SpawnLocation = Origin + GetActorRightVector() * (StartX + Index * ItemSpacing);
		
		// Make item face the curved LookAtPoint
		const FVector DirectionToLookAt = (LookAtPoint - SpawnLocation).GetSafeNormal();
		const FRotator SpawnRotation = DirectionToLookAt.Rotation();

		if (AHYUpgradeItem* Item = GetWorld()->SpawnActor<AHYUpgradeItem>(ItemClass, SpawnLocation, SpawnRotation, SpawnParams))
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

