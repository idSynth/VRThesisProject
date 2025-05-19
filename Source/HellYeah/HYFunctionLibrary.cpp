// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.


#include "HYFunctionLibrary.h"
#include "GameplayTagsManager.h"
#include "Algo/Reverse.h"

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

FGameplayTagContainer UHYFunctionLibrary::GetGameplayTagChildren(FGameplayTag Tag)
{
	const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	return Manager.RequestGameplayTagChildren(Tag);
}

FGameplayTagContainer UHYFunctionLibrary::GetGameplayTagParents(FGameplayTag Tag)
{
	const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	return Manager.RequestGameplayTagParents(Tag);
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
