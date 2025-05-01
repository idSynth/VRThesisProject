// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/HYDamageableActor.h"
#include "Interfaces/HYModifierProvider.h"
#include "HYStage.generated.h"

/**
 * 
 */
UCLASS()
class HELLYEAH_API AHYStage : public AHYDamageableActor, public IHYModifierProvider
{
	GENERATED_BODY()
	
public:
	FModifyAttribute ModifyAttribute;
	virtual FModifyAttribute* GetModifierDelegate() override { return HealthComponent->GetModifierDelegate(); }
};
