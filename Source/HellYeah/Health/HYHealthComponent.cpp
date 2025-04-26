// Fill out your copyright notice in the Description page of Project Settings.


#include "HellYeah/Health/HYHealthComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/HYCameraFacingWidgetComponent.h"
#include "Widgets/HYOwnableWidget.h"

// Sets default values for this component's properties
UHYHealthComponent::UHYHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

float UHYHealthComponent::TryDamage(const FHYDamageInfo& InDamageInfo)
{
	if (IsDead() || !InDamageInfo.IsValidDamageInfo())
	{
		return 0.0f;
	}

	float OldHealth = CurrentHealth;

	float CalculatedDamage = CalculateDamage(InDamageInfo);

	CurrentHealth = FMath::Max(CurrentHealth - CalculatedDamage, 0.0f);

	if (!IsDead() && CalculatedDamage == 0.0f)
	{
		OnHitBlocked.Broadcast(InDamageInfo);
		return CalculatedDamage;
	}
	
	if (CalculatedDamage != 0.0f)
	{
		OnHealthChanged.Broadcast(CurrentHealth, OldHealth);
	}

	if (IsDead())
	{
		OnDeath.Broadcast(InDamageInfo);
	}

	return CalculatedDamage;
}

void UHYHealthComponent::OverrideHealth(const float& NewHealth)
{
	float OldHealth = CurrentHealth;
	
	CurrentHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);

	if (CurrentHealth - NewHealth != 0.0f)
	{
		OnHealthChanged.Broadcast(CurrentHealth, OldHealth);
	}

	if (NewHealth <= 0.0f)
	{
		OnDeath.Broadcast(FHYDamageInfo());
	}

}

float UHYHealthComponent::CalculateDamage(const FHYDamageInfo& InDamageInfo)
{
	float NewDamage = FMath::Abs(InDamageInfo.Damage);

	return NewDamage;
}

void UHYHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	OverrideHealth(MaxHealth);

	SetupHealthBar();
}

bool UHYHealthComponent::SetupHealthBar()
{
	AActor* Owner = GetOwner();

	if (!Owner || !HealthBarWidgetClass)
	{
		return false;
	}

	FTransform AttachmentTransform = FTransform();
	AttachmentTransform.SetLocation(HealthBarOffset);

	bool bShouldAttachToSocket = !HealthBarAttachSocket.IsNone();

	WidgetComponent = Cast<UHYCameraFacingWidgetComponent>(Owner->AddComponentByClass(UHYCameraFacingWidgetComponent::StaticClass(), bShouldAttachToSocket, AttachmentTransform, true));

	if (!IsValid(WidgetComponent))
	{
		return false;
	}

	if (bShouldAttachToSocket)
	{
		USkeletalMeshComponent* SkeletalMeshComp = Owner->FindComponentByClass<USkeletalMeshComponent>();

		if (IsValid(SkeletalMeshComp) && SkeletalMeshComp->DoesSocketExist(HealthBarAttachSocket))
		{
			WidgetComponent->SetupAttachment(SkeletalMeshComp, HealthBarAttachSocket);
		}
	}

	WidgetComponent->SetWidgetClass(HealthBarWidgetClass);

	WidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	WidgetComponent->SetDrawAtDesiredSize(false);
	WidgetComponent->SetDrawSize(HealthBarSize);

	Owner->FinishAddComponent(WidgetComponent, bShouldAttachToSocket, AttachmentTransform);

	Cast<UHYOwnableWidget>(WidgetComponent->GetWidget())->SetWidgetOwner(Owner);

	OnHealthBarSetup.Broadcast(WidgetComponent);

	return true;
}

