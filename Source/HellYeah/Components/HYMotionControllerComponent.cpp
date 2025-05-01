// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HYMotionControllerComponent.h"

FVector UHYMotionControllerComponent::GetLinearVelocityPublic()
{
	FVector OutVelocity;
	GetLinearVelocity(OutVelocity);
	return OutVelocity;
}
