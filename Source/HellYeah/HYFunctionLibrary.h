// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Core/HYGameState.h"
#include "Core/HYPlayerState.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "Actors/Gameplay/HYWaveManager.h"
#include "Actors/Gameplay/HYUpgradeSelector.h"
#include "Kismet/GameplayStatics.h"
#include "HYStructs.h"
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
	static AHYWaveManager* GetWaveManager() { return Cast<AHYWaveManager>(UGameplayStatics::GetActorOfClass(GWorld, AHYWaveManager::StaticClass())); }

	UFUNCTION(BlueprintCallable)
	static AHYUpgradeSelector* GetUpgradeSelector() { return Cast<AHYUpgradeSelector>(UGameplayStatics::GetActorOfClass(GWorld, AHYUpgradeSelector::StaticClass())); }

	UFUNCTION(BlueprintCallable)
	static AHYEnemyBase* SpawnEnemyFromType(const FGameplayTag& Type, const FTransform& Transform);

	UFUNCTION(BlueprintCallable)
	static AHYEnemyBase* SpawnEnemyFromDescription(const FHYEnemyDescription& EnemyDescription, const FTransform& Transform);

	UFUNCTION(BlueprintCallable)
	static FHYEnemyDescription GetDescriptionFromEnemyType(const FGameplayTag& Type);

	// Returns container that excludes B from A
	UFUNCTION(BlueprintCallable)
	static FGameplayTagContainer FilterContainer(const FGameplayTagContainer& A, const FGameplayTagContainer& B);

	UFUNCTION(BlueprintCallable)
	static FGameplayTagContainer GetGameplayTagChildren(FGameplayTag Tag) { return UGameplayTagsManager::Get().RequestGameplayTagChildren(Tag); }
	
	UFUNCTION(BlueprintCallable)
	static FGameplayTagContainer GetGameplayTagParents(FGameplayTag Tag) { return UGameplayTagsManager::Get().RequestGameplayTagParents(Tag); }
	
	UFUNCTION(BlueprintCallable)
	static FGameplayTag GetRandomTag(const FGameplayTagContainer& Container) { return Container.GetByIndex(FMath::RandRange(0, Container.Num() - 1)); }

	UFUNCTION(BlueprintCallable)
	static FGameplayTagContainer GetGameplayTagLastChildrenOnly(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable)
	static FText GetFriendlyAttributeName(const FGameplayTag& Tag);
};
