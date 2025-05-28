// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.


#include "HYFunctionLibrary.h"
#include "Algo/Reverse.h"
#include "Characters/HYEnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"

FText UHYFunctionLibrary::GetFriendlyAttributeName(const FGameplayTag& Tag)
{
	FString TagString = Tag.ToString();

	// Strip "Attribute." prefix
	const FString Prefix = "Attribute.";
	if (TagString.StartsWith(Prefix))
	{
		TagString = TagString.RightChop(Prefix.Len());
	}

	// Split, reverse, and capitalize parts
	TArray<FString> Parts;
	TagString.ParseIntoArray(Parts, TEXT("."), true);
	Algo::Reverse(Parts);

	return FText::FromString(FString::Join(Parts, TEXT(" ")));
}

AHYEnemyBase* UHYFunctionLibrary::SpawnEnemyFromType(const FGameplayTag& Type, const FTransform& Transform)
{
	if (AHYEnemyBase* Enemy = SpawnEnemyFromDescription(GetDescriptionFromEnemyType(Type), Transform))
	{
		Enemy->SetType(Type);

		return Enemy;
	}

	return nullptr;
}

AHYEnemyBase* UHYFunctionLibrary::SpawnEnemyFromDescription(const FHYEnemyDescription& EnemyDescription, const FTransform& Transform)
{
	FTransform FinalTransform = Transform;
	FinalTransform.SetScale3D(FVector(EnemyDescription.Scale));

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AHYEnemyBase* SpawnedActor = GWorld->SpawnActor<AHYEnemyBase>(EnemyDescription.Class.LoadSynchronous(), FinalTransform, SpawnParams);
	
	if (!IsValid(SpawnedActor))
	{
		return nullptr;
	}

	SpawnedActor->SetDescription(EnemyDescription);

	return SpawnedActor;
}

FHYEnemyDescription UHYFunctionLibrary::GetDescriptionFromEnemyType(const FGameplayTag& Type)
{
	const UHYTagData* TagData = GetDefault<UHYTagData>();

	for (TSoftObjectPtr<UDataTable> DTSoft : TagData->TagsDT)
	{
		UDataTable* DataTable = DTSoft.LoadSynchronous();
		if (!DataTable)
		{
			continue;
		}

		// Check if the row structure is of type FHYEnemyDescription
		if (DataTable->GetRowStruct() == FHYEnemyDescription::StaticStruct())
		{
			if (FHYEnemyDescription* Row = DataTable->FindRow<FHYEnemyDescription>(Type.GetTagName(), TEXT("GetDescriptionFromEnemyType")))
			{
				return *Row;
			}
		}
	}

	// Return a default-initialized struct if not found
	return FHYEnemyDescription();
}

FGameplayTagContainer UHYFunctionLibrary::FilterContainer(const FGameplayTagContainer& A, const FGameplayTagContainer& B)
{
	TArray<FGameplayTag> GameplayTags;
	A.GetGameplayTagArray(GameplayTags);

	FGameplayTagContainer ResultContainer;

	for (const FGameplayTag& Tag : GameplayTags)
	{
		if (!Tag.MatchesAny(B))
		{
			ResultContainer.AddTagFast(Tag);
		}
	}

	return ResultContainer;
}

FGameplayTagContainer UHYFunctionLibrary::GetGameplayTagLastChildrenOnly(FGameplayTag Tag)
{
	FGameplayTagContainer OutTags;
	TArray<FGameplayTag> AllChildrenArray = GetGameplayTagChildren(Tag).GetGameplayTagArray();

	for (const FGameplayTag& Child : AllChildrenArray)
	{
		if (GetGameplayTagChildren(Child).IsEmpty())
		{
			OutTags.AddTag(Child);
		}
	}

	return OutTags;
}
