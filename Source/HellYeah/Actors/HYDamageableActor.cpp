// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.


#include "Actors/HYDamageableActor.h"
#include "Health/HYHealthComponent.h"

// Sets default values
AHYDamageableActor::AHYDamageableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHYHealthComponent>(TEXT("Health Component"));
}

// Called when the game starts or when spawned
void AHYDamageableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHYDamageableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

