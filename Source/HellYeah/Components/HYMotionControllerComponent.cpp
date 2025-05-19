// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.


#include "Components/HYMotionControllerComponent.h"

FVector UHYMotionControllerComponent::GetLinearVelocityPublic()
{
	FVector OutVelocity;
	GetLinearVelocity(OutVelocity);
	return OutVelocity;
}
