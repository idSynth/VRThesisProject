// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HYModifierProvider.h"
#include "Health/HYHealthComponent.h"
#include "HYCharacter.generated.h"

class UHYHealthComponent;

UCLASS(Abstract)
class HELLYEAH_API AHYCharacter : public ACharacter, public IHYModifierProvider
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHYCharacter();

	FModifyAttribute ModifyAttribute;
	virtual TArray<FModifyAttribute*> GetModifierDelegates() override;

	UFUNCTION(BlueprintCallable, Category = "HYCharacter|Health")
	UHYHealthComponent* GetHealthComponent() const { return HealthComponent; };

	UFUNCTION(BlueprintCallable)
	bool DealDamage(const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HYCharacter|Health")
	TObjectPtr<UHYHealthComponent> HealthComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UFUNCTION(BlueprintCallable)
	float GetBaseDamage() const { return BaseDamage; }

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	float BaseDamage = 10.0f;
};
