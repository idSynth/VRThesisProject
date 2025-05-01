// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MotionControllerComponent.h"
#include "HYMotionControllerComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent), ClassGroup = MotionController)
class HELLYEAH_API UHYMotionControllerComponent : public UMotionControllerComponent
{
	GENERATED_BODY()
	
public:
	FVector GetLinearVelocityPublic();
};
