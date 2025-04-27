// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Gameplay/HYUpgradeSelector.h"

// Sets default values
AHYUpgradeSelector::AHYUpgradeSelector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AHYUpgradeSelector::StartUpgradeSelection()
{
	OnUpgradeSelectionStarted.Broadcast();
}

void AHYUpgradeSelector::FinishUpgradeSelection()
{
	OnUpgradeSelected.Broadcast();
}

// Called when the game starts or when spawned
void AHYUpgradeSelector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHYUpgradeSelector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

