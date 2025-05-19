// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.


#include "Subsystems/UpgradeLoaderSubsystem.h"
#include "GameplayTagsManager.h"

DEFINE_LOG_CATEGORY(LogUpgradeLoader);

void UUpgradeLoaderSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UHYUpgradesData* UpgradesData = GetDefault<UHYUpgradesData>();

	UDataTable* DataTable = UpgradesData->UpgradesDT.LoadSynchronous();

	if (!DataTable)
	{
		UE_LOG(LogUpgradeLoader, Error, TEXT("No DataTable found for Upgrades!"));
		return;
	}

	UGameplayTagsManager& TagManager = UGameplayTagsManager::Get();

	TArray<FName> UpgradeNames = DataTable->GetRowNames();

	for (const FName& Name : UpgradeNames)
	{
		if (!TagManager.IsValidGameplayTagString(*Name.ToString()))
		{
			UE_LOG(LogUpgradeLoader, Error, TEXT("Tag %s is not valid and cannot be added! Please check for tag syntax!"), *Name.ToString());

			continue;
		}

		TagManager.AddNativeGameplayTag(Name, TEXT("Added from UpgradeLoader"));
		UE_LOG(LogUpgradeLoader, Log, TEXT("Successfully added Upgrade Tag %s"), *Name.ToString());
	}
}
