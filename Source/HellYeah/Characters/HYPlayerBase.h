// Fill out your copyright notice in the Description page of Project Settings.

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
