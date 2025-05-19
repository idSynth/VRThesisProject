// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HYGrabComponent.generated.h"

class UHapticFeedbackEffect_Base;
class UHYMotionControllerComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGrabbed, UHYMotionControllerComponent*, MotionController);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDropped, UHYMotionControllerComponent*, LastMotionController);

UENUM(Blueprintable)
enum class EGrabType : uint8
{
	None,
	Free,
	Snap,
	Custom
};

UCLASS(Blueprintable)
class HELLYEAH_API UHYGrabComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHYGrabComponent();
	
	UFUNCTION(BlueprintCallable)
	bool TryGrab(UHYMotionControllerComponent* MotionController);

	UFUNCTION(BlueprintCallable)
	bool TryRelease();

	UFUNCTION(BlueprintCallable)
	void SetShouldSimulateOnDrop();

	UFUNCTION(BlueprintCallable)
	void SetPrimitiveCompPhysics(bool bSimulate);

	UFUNCTION(BlueprintCallable)
	EControllerHand GetHeldByHand() const;
	
	UFUNCTION(BlueprintCallable)
	bool AttachParentToMotionController(UHYMotionControllerComponent* MotionController);

	// ========================================================

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsHeld;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FRotator PrimaryGrabRelativeRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bSimulateOnDrop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EGrabType GrabType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UHapticFeedbackEffect_Base> OnGrabHapticEffect;

	UPROPERTY(BlueprintAssignable)
	FOnGrabbed OnGrabbed;

	UPROPERTY(BlueprintAssignable)
	FOnDropped OnDropped;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UHYMotionControllerComponent> MotionControllerRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UHYGrabComponent> PrimaryGrabComponent;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
