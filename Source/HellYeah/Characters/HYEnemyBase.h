// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/HYCharacter.h"
#include "Components/HYInventoryComponent.h"
#include "HYEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class HELLYEAH_API AHYEnemyBase : public AHYCharacter
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	UHYInventoryComponent* GetInventoryComponent() const { return Inventory; }

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UHYInventoryComponent> Inventory;
};
