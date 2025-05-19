// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

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
