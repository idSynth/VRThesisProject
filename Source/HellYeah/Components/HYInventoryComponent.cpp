// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.


#include "Components/HYInventoryComponent.h"
#include "HYGameplayTags.h"
#include "HYStructs.h"
#include "Upgrades/HYUpgrade.h"

// Sets default values for this component's properties
UHYInventoryComponent::UHYInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UHYInventoryComponent::AddNumStacks(const FGameplayTag& UpgradeTag, int32 NumStacks)
{
	const int32* CurrentStacksPtr = Upgrades.Find(UpgradeTag);
	int32 PreviousStacks = CurrentStacksPtr ? *CurrentStacksPtr : 0;

	for (int32 i = 0; i <= NumStacks; i++)
	{
		AddStack(UpgradeTag);
	}
}

void UHYInventoryComponent::RemoveAllStacks(const FGameplayTag& UpgradeTag)
{
	const int32* CurrentStacksPtr = Upgrades.Find(UpgradeTag);
	if (!CurrentStacksPtr)
	{
		return;
	}

	int32 PreviousStacks = *CurrentStacksPtr;
	int32 NewStacks = 0;

	if (NewStacks <= 0)
	{
		Upgrades.Remove(UpgradeTag);

		// Uninitialize and remove upgrade object
		if (UHYUpgrade** UpgradePtr = ActiveUpgrades.Find(UpgradeTag))
		{
			if (UHYUpgrade* Upgrade = *UpgradePtr)
			{
				Upgrade->UninitializeUpgrade(this);
			}

			ActiveUpgrades.Remove(UpgradeTag);
		}
	}

	// Broadcast the change
	OnStackChanged.Broadcast(UpgradeTag, PreviousStacks, NewStacks);
}

bool UHYInventoryComponent::AddStack(const FGameplayTag& UpgradeTag)
{
	FHYUpgradeData* Row = UpgradeDT->FindRow<FHYUpgradeData>(UpgradeTag.GetTagName(), TEXT("AddStack()"));

	if (!Row)
	{
		return false;
	}

	// Get previous stack count (0 if new)
	const int32* CurrentStacksPtr = Upgrades.Find(UpgradeTag);
	int32 PreviousStacks = CurrentStacksPtr ? *CurrentStacksPtr : 0;
	int32 NewStacks = PreviousStacks + 1;

	// Save updated stack count
	Upgrades.Add(UpgradeTag, NewStacks);

	// Handle upgrade object
	UHYUpgrade** UpgradePtr = ActiveUpgrades.Find(UpgradeTag);
	UHYUpgrade* Upgrade = UpgradePtr ? *UpgradePtr : nullptr;

	if (!Upgrade && NewStacks == 1)
	{
		// First time this upgrade is applied create and initialize it
		Upgrade = NewObject<UHYUpgrade>(this, Row->UpgradeClass.LoadSynchronous());
		Upgrade->SetTag(UpgradeTag);
		Upgrade->SetUpgradeData(*Row);
		Upgrade->InitializeUpgrade(this);

		ActiveUpgrades.Add(UpgradeTag, Upgrade);
	}
	else if (Upgrade)
	{
		// Already exists notify it of the stack change
		Upgrade->OnStackChanged(NewStacks);
	}

	OnStackChanged.Broadcast(UpgradeTag, PreviousStacks, NewStacks);

	return true;
}


bool UHYInventoryComponent::RemoveStack(const FGameplayTag& UpgradeTag)
{
	const int32* CurrentStacksPtr = Upgrades.Find(UpgradeTag);
	if (!CurrentStacksPtr)
	{
		return false;
	}

	int32 PreviousStacks = *CurrentStacksPtr;
	int32 NewStacks = PreviousStacks - 1;

	if (NewStacks <= 0)
	{
		Upgrades.Remove(UpgradeTag);

		// Uninitialize and remove upgrade object
		if (UHYUpgrade** UpgradePtr = ActiveUpgrades.Find(UpgradeTag))
		{
			if (UHYUpgrade* Upgrade = *UpgradePtr)
			{
				Upgrade->UninitializeUpgrade(this);
			}

			ActiveUpgrades.Remove(UpgradeTag);
		}
	}
	else
	{
		Upgrades.Add(UpgradeTag, NewStacks);

		// Notify the upgrade about the stack change
		if (UHYUpgrade** UpgradePtr = ActiveUpgrades.Find(UpgradeTag))
		{
			if (UHYUpgrade* Upgrade = *UpgradePtr)
			{
				Upgrade->OnStackChanged(NewStacks);
			}
		}
	}

	// Broadcast the change
	OnStackChanged.Broadcast(UpgradeTag, PreviousStacks, NewStacks);

	return true;
}

int32 UHYInventoryComponent::GetStacksByTag(const FGameplayTag& UpgradeTag)
{	
	// Get stack count (0 if nothing found)
	const int32* CurrentStacksPtr = Upgrades.Find(UpgradeTag);
	return CurrentStacksPtr ? *CurrentStacksPtr : 0;
}

UHYUpgrade* UHYInventoryComponent::GetUpgradeByTag(const FGameplayTag& UpgradeTag)
{
	if (UHYUpgrade** UpgradePtr = ActiveUpgrades.Find(UpgradeTag))
	{
		return *UpgradePtr;
	}

	return nullptr;
}

// Called when the game starts
void UHYInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UHYInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

