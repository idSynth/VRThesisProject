// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "HYStructs.h"
#include "HYUpgrade.generated.h"

class UHYInventoryComponent;
class AHYCharacter;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class HELLYEAH_API UHYUpgrade : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	AActor* GetListenActor();

	bool BindModifierDelegate();
	bool UnbindModifierDelegate();

	UFUNCTION(BlueprintCallable)
	virtual bool InitializeUpgrade(UHYInventoryComponent* InOwner);

	UFUNCTION(BlueprintCallable)
	virtual bool UninitializeUpgrade(UHYInventoryComponent* InOwner);

	UFUNCTION(BlueprintCallable)
	virtual bool Activate();

	UFUNCTION()
	void ModifyAttribute(const FGameplayTag& InAttributeTag, float& Attribute);

	UFUNCTION(BlueprintNativeEvent)
	float ModifyAttributeBP(const FGameplayTag& InAttributeTag, const float& Attribute);

	// Blueprint Events

	UFUNCTION(BlueprintImplementableEvent)
	void OnStackChanged(int32 NewStacks);

	UFUNCTION(BlueprintImplementableEvent)
	void OnInitialized();

	UFUNCTION(BlueprintImplementableEvent)
	void OnUninitialized();

	UFUNCTION(BlueprintImplementableEvent)
	void OnActivated();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCooldownFinished();

	// Blueprint Events End

	UFUNCTION(BlueprintCallable)
	bool IsOnCooldown() const { return GetWorld()->GetTimerManager().IsTimerActive(Cooldown); }

	UFUNCTION(BlueprintCallable)
	FGameplayTag GetTag() const { return Tag; }
	
	UFUNCTION(BlueprintCallable)
	void SetTag(const FGameplayTag& InTag) { Tag = InTag; }

	UFUNCTION(BlueprintCallable)
	void SetUpgradeData(const FHYUpgradeData& Data);

	UFUNCTION(BlueprintCallable)
	UHYInventoryComponent* GetOwner() const { return Owner; }

	UFUNCTION(BlueprintCallable)
	void SetOwner(UHYInventoryComponent* InOwner) { Owner = InOwner; }

	UFUNCTION(BlueprintCallable)
	AHYCharacter* GetOwningCharacter();

	UFUNCTION(BlueprintCallable)
	float GetPercentFromStacks() const;

protected:
	UPROPERTY(BlueprintReadOnly)
	UHYInventoryComponent* Owner;

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag Tag;

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag AttributeTag;

	UPROPERTY(BlueprintReadOnly)
	EListenActor ListenTarget;

	UPROPERTY(BlueprintReadOnly)
	EModifierType ModifierType;

	UPROPERTY(BlueprintReadOnly)
	float PercentPerStack = 0.1f;

	UPROPERTY(BlueprintReadOnly)
	float CooldownDuration;

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle Cooldown;

	FDelegateHandle ModifierDelegateHandle;
};
