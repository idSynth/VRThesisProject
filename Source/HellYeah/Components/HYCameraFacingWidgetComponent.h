// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HYCameraFacingWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class HELLYEAH_API UHYCameraFacingWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UHYCameraFacingWidgetComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
