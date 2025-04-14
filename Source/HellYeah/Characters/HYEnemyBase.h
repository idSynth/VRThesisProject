// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/HYCharacter.h"
#include "HYEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class HELLYEAH_API AHYEnemyBase : public AHYCharacter
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	float GetBaseDamage() const { return BaseDamage; }

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	float BaseDamage = 10.0f;
};
