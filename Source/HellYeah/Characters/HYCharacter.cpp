// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.


#include "Characters/HYCharacter.h"
#include "Health/HYHealthComponent.h"
#include "HYGameplayTags.h"

// Sets default values
AHYCharacter::AHYCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHYHealthComponent>(TEXT("Health Component"));
}

TArray<FModifyAttribute*> AHYCharacter::GetModifierDelegates()
{
	TArray<FModifyAttribute*> Delegates;

	Delegates.Add(&ModifyAttribute);

	if (UHYHealthComponent* Health = FindComponentByClass<UHYHealthComponent>())
	{
		if (IHYModifierProvider* HealthProvider = Cast<IHYModifierProvider>(Health))
		{
			Delegates.Append(HealthProvider->GetModifierDelegates());
		}
	}

	return Delegates;
}

bool AHYCharacter::DealDamage(const FHitResult& Hit)
{
	if (!Hit.bBlockingHit)
	{
		return false;
	}

	if (!IsValid(Hit.GetActor()))
	{
		return false;
	}

	if (UHYHealthComponent* HealthComp = Hit.GetActor()->GetComponentByClass<UHYHealthComponent>())
	{
		float FinalDamage = BaseDamage;
		ModifyAttribute.Broadcast(TAG_Attribute_Damage_Outcoming, FinalDamage);

		FHYDamageInfo DamageInfo;
		DamageInfo.Damage = FinalDamage;
		DamageInfo.DamageCauser = this;
		DamageInfo.Instigator = this;
		DamageInfo.HitResult = Hit;

		HealthComp->TryDamage(DamageInfo);
		return true;
	}
	
	return true;
}

// Called when the game starts or when spawned
void AHYCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHYCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHYCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

