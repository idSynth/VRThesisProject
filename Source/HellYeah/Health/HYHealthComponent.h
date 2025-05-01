// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/HYModifierProvider.h"
#include "HYHealthComponent.generated.h"

class UHYCameraFacingWidgetComponent;
class UHYOwnableWidget;

USTRUCT(BlueprintType)
struct FHYDamageInfo
{
	GENERATED_BODY()
	
public:
	FHYDamageInfo()
	{
	}

	UPROPERTY(BlueprintReadWrite)
	float Damage = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	APawn* Instigator;

	UPROPERTY(BlueprintReadWrite)
	AActor* DamageCauser;

	UPROPERTY(BlueprintReadWrite)
	FHitResult HitResult;

	bool IsValidDamageInfo() const { return Damage != 0.0f; }

	AActor* GetTarget() const { return HitResult.GetActor(); }
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHitBlocked, FHYDamageInfo, BlockedDamageInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, OldHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, FHYDamageInfo, LethalDamageInfo);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthBarSetup, UWidgetComponent*, HealthBarComponent);


UCLASS( BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELLYEAH_API UHYHealthComponent : public UActorComponent, public IHYModifierProvider
{
	GENERATED_BODY()

public:	
	UHYHealthComponent();

	FModifyAttribute ModifyAttribute;
	virtual FModifyAttribute* GetModifierDelegate() override { return &ModifyAttribute; }

	// Tries damaging an actor, returns the amount of damage dealt
	UFUNCTION(BlueprintCallable)
	float TryDamage(const FHYDamageInfo& InDamageInfo);

	UFUNCTION(BlueprintCallable)
	void OverrideHealth(const float& NewHealth);

	// Getters

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const { return CurrentHealth <= 0.0f; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercentage() const { return CurrentHealth / MaxHealth; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	FHYDamageInfo GetLastDamageInfo() const { return LastDamageInfo; }

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnHitBlocked OnHitBlocked;

	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable)
	FOnHealthBarSetup OnHealthBarSetup;

protected:
	virtual void BeginPlay() override;

	bool SetupHealthBar();

	float CalculateDamage(const FHYDamageInfo& InDamageInfo);

	// Health

	UPROPERTY()
	float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth = 100.0f;

	// Health Bar
	UPROPERTY(EditDefaultsOnly, Category = "HealthBar")
	TSubclassOf<UHYOwnableWidget> HealthBarWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "HealthBar")
	FVector HealthBarOffset;

	UPROPERTY(EditDefaultsOnly, Category = "HealthBar")
	FVector2D HealthBarSize;

	UPROPERTY(EditDefaultsOnly, Category = "HealthBar")
	FName HealthBarAttachSocket;


	UPROPERTY()
	FHYDamageInfo LastDamageInfo;

	UPROPERTY()
	TObjectPtr<UHYCameraFacingWidgetComponent> WidgetComponent;
};
