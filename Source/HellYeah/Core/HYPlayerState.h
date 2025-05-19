// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "HYPlayerState.generated.h"

class UHYInventoryComponent;

/**
 * 
 */
UCLASS()
class HELLYEAH_API AHYPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AHYPlayerState();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UHYInventoryComponent> InventoryComponent;
};
