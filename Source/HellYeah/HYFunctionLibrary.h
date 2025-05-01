// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Core/HYGameState.h"
#include "Core/HYPlayerState.h"
#include "GameplayTagContainer.h"
#include "HYFunctionLibrary.generated.h"

class UMotionControllerComponent;

/**
 * 
 */
UCLASS()
class HELLYEAH_API UHYFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	static AHYGameState* GetGameStateTyped() { return GWorld->GetGameStateChecked<AHYGameState>(); }

	UFUNCTION(BlueprintCallable)
	static AHYPlayerState* GetPlayerStateTyped() { return GWorld->GetFirstPlayerController()->GetPlayerState<AHYPlayerState>(); }

	UFUNCTION(BlueprintCallable)
	static FText GetFriendlyAttributeName(const FGameplayTag& Tag);
};
