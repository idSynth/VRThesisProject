// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "HYInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnStackChanged, FGameplayTag, ChangedTag, int32, OldStacks, int32, NewStacks);

class UHYUpgrade;

UCLASS( BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELLYEAH_API UHYInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHYInventoryComponent();

	UPROPERTY(BlueprintAssignable)
	FOnStackChanged OnStackChanged;

	UFUNCTION(BlueprintCallable)
	void AddNumStacks(const FGameplayTag& UpgradeTag, int32 NumStacks);

	UFUNCTION(BlueprintCallable)
	void RemoveAllStacks(const FGameplayTag& UpgradeTag);

	UFUNCTION(BlueprintCallable)
	bool AddStack(const FGameplayTag& UpgradeTag);

	UFUNCTION(BlueprintCallable)
	bool RemoveStack(const FGameplayTag& UpgradeTag);

	UFUNCTION(BlueprintCallable)
	int32 GetStacksByTag(const FGameplayTag& UpgradeTag);

	UFUNCTION(BlueprintCallable)
	UHYUpgrade* GetUpgradeByTag(const FGameplayTag& UpgradeTag);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FGameplayTag, int32> Upgrades;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FGameplayTag, UHYUpgrade*> ActiveUpgrades;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UDataTable> UpgradeDT;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
