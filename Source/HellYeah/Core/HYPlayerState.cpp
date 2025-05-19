// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.


#include "Core/HYPlayerState.h"
#include "Components/HYInventoryComponent.h"

AHYPlayerState::AHYPlayerState()
{
	InventoryComponent = CreateDefaultSubobject<UHYInventoryComponent>(TEXT("InventoryComponent"));
}
