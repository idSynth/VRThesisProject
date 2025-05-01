// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HYPlayerState.h"
#include "Components/HYInventoryComponent.h"

AHYPlayerState::AHYPlayerState()
{
	InventoryComponent = CreateDefaultSubobject<UHYInventoryComponent>(TEXT("InventoryComponent"));
}
