// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.


#include "Subsystems/TagLoaderSubsystem.h"
#include "GameplayTagsManager.h"

DEFINE_LOG_CATEGORY(LogTagLoader);

void UTagLoaderSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UGameplayTagsManager::Get().OnLastChanceToAddNativeTags().AddUObject(this, &UTagLoaderSubsystem::RegisterAllTags);
}

void UTagLoaderSubsystem::RegisterAllTags()
{
	const UHYTagData* TagData = GetDefault<UHYTagData>();

	for (TSoftObjectPtr<UDataTable> DT : TagData->TagsDT)
	{
		RegisterTagsFromDataTableRows(DT.LoadSynchronous());
	}
}

void UTagLoaderSubsystem::RegisterTagsFromDataTableRows(UDataTable* DT)
{
	if (!DT)
	{
		UE_LOG(LogTagLoader, Error, TEXT("Invalid DataTable passed in!"));
		return;
	}

	UGameplayTagsManager& TagManager = UGameplayTagsManager::Get();

	TArray<FName> UpgradeNames = DT->GetRowNames();

	for (const FName& Name : UpgradeNames)
	{
		if (!TagManager.IsValidGameplayTagString(*Name.ToString()))
		{
			UE_LOG(LogTagLoader, Error, TEXT("Tag %s is not valid and cannot be added! Please check for tag syntax!"), *Name.ToString());

			continue;
		}

		TagManager.AddNativeGameplayTag(Name, TEXT("Added from TagLoader"));
		UE_LOG(LogTagLoader, Log, TEXT("Successfully added Tag %s"), *Name.ToString());
	}
}
