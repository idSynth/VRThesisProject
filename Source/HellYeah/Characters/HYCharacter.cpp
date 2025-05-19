// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.


#include "Characters/HYCharacter.h"
#include "Health/HYHealthComponent.h"

// Sets default values
AHYCharacter::AHYCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHYHealthComponent>(TEXT("Health Component"));
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

