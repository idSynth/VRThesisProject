// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.


#include "Components/HYCameraFacingWidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


UHYCameraFacingWidgetComponent::UHYCameraFacingWidgetComponent()
{
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void UHYCameraFacingWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0))
	{
		SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(GetComponentLocation(), CameraManager->GetCameraLocation()));
	}
}
