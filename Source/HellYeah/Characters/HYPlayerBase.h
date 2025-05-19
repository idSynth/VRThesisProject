// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/HYCharacter.h"
#include "HYPlayerBase.generated.h"

class AHYGuitarBase;

/**
 * 
 */
UCLASS()
class HELLYEAH_API AHYPlayerBase : public AHYCharacter
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AHYGuitarBase> Guitar;
};
