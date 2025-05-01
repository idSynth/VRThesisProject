// Fill out your copyright notice in the Description page of Project Settings.


#include "HYFunctionLibrary.h"
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