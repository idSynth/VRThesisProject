// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/HYCharacter.h"
#include "Components/HYInventoryComponent.h"
#include "AI/HYAIController.h"
#include "HYStructs.h"
#include "HYEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class HELLYEAH_API AHYEnemyBase : public AHYCharacter
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	UHYInventoryComponent* GetInventoryComponent() const { return Inventory; }

	UFUNCTION(BlueprintCallable)
	AHYAIController* GetAIControllerTyped() const { return Cast<AHYAIController>(GetController()); }

	UFUNCTION(BlueprintCallable)
	void Stun(float MovementSpeedMultiplier, float RecoveryTimeMultiplier);

	UFUNCTION(BlueprintCallable)
	void ResetStun();

	UFUNCTION(BlueprintCallable)
	FGameplayTag GetType() const { return Type; }

	UFUNCTION(BlueprintCallable)
	void SetType(const FGameplayTag& NewType) { Type = NewType; }

	UFUNCTION(BlueprintCallable)
	FHYEnemyDescription GetDescription() const { return Description; }

	UFUNCTION(BlueprintCallable)
	void SetDescription(const FHYEnemyDescription& NewDescription);

	UFUNCTION(BlueprintCallable)
	void StartCurrentBehaviorTree();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FHYEnemyDescription Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UHYInventoryComponent> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RecoveryTime = 0.5;

	UPROPERTY(BlueprintReadOnly)
	float DefaultWalkSpeed;

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle StunTimer;
};
