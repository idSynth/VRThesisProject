// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

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
	virtual TArray<FModifyAttribute*> GetModifierDelegates() override { return HealthComponent->GetModifierDelegates(); }
};
