// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HYGrabComponent.h"
#include "Components/HYMotionControllerComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHYGrabComponent::UHYGrabComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UHYGrabComponent::TryGrab(UHYMotionControllerComponent* MotionController)
{
	switch (GrabType)
	{
		case EGrabType::None:
		{
			return false;
		}
		case EGrabType::Free:
		{
			SetPrimitiveCompPhysics(false);
			bIsHeld = AttachParentToMotionController(MotionController);
			break;
		}
		case EGrabType::Snap:
		{
			bIsHeld = AttachParentToMotionController(MotionController);
			if (bIsHeld)
			{	
				if (USceneComponent* Parent = GetAttachParent())
				{
					Parent->SetRelativeRotation(GetRelativeRotation().GetInverse());

					FVector NewLocation = MotionController->GetComponentLocation() + (GetComponentLocation() - Parent->GetComponentLocation()) * -1.0f;
					Parent->SetWorldLocation(NewLocation);
				}
			}

			break;
		}
		case EGrabType::Custom:
		{
			bIsHeld = true;
			break;
		}
	}

	if (!bIsHeld)
	{
		return false;
	}

	MotionControllerRef = MotionController;

	OnGrabbed.Broadcast(MotionControllerRef);

	UGameplayStatics::GetPlayerController(this, 0)->PlayHapticEffect(OnGrabHapticEffect, GetHeldByHand());

	return true;
}

bool UHYGrabComponent::TryRelease()
{
	switch (GrabType)
	{
		case EGrabType::None:
		{
			return false;
		}
		case EGrabType::Free:
		case EGrabType::Snap:
		{
			if (bSimulateOnDrop)
			{
				SetPrimitiveCompPhysics(true);
			}
			else
			{
				if (USceneComponent* Parent = GetAttachParent())
				{
					Parent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
				}
			}

			bIsHeld = false;
			break;
		}
		case EGrabType::Custom:
		{
			bIsHeld = false;
			break;
		}
	}

	if (bIsHeld)
	{
		return false;
	}
	
	OnDropped.Broadcast(MotionControllerRef);

	return true;
}

void UHYGrabComponent::SetShouldSimulateOnDrop()
{
	if (UPrimitiveComponent* PrimComponent = Cast<UPrimitiveComponent>(GetAttachParent()))
	{
		bSimulateOnDrop = PrimComponent->IsSimulatingPhysics();
	}
}

void UHYGrabComponent::SetPrimitiveCompPhysics(bool bSimulate)
{
	if (UPrimitiveComponent* PrimComponent = Cast<UPrimitiveComponent>(GetAttachParent()))
	{
		PrimComponent->SetSimulatePhysics(bSimulate);
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("Failed PrimitiveComponent cast in SetPrimitiveCompPhysics()!"));
}

EControllerHand UHYGrabComponent::GetHeldByHand() const
{
	return MotionControllerRef->MotionSource == FName("LeftGrip") ? EControllerHand::Left : EControllerHand::Right;
}

bool UHYGrabComponent::AttachParentToMotionController(UHYMotionControllerComponent* MotionController)
{
	USceneComponent* Parent = GetAttachParent();
	if (!IsValid(Parent))
	{
		return false;
	}

	return Parent->AttachToComponent(MotionController, FAttachmentTransformRules::KeepWorldTransform);
}


// Called when the game starts
void UHYGrabComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHYGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

