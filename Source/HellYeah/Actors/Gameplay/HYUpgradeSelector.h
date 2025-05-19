// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "HYUpgradeSelector.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpgradeSelected, FGameplayTag, SelectedTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpgradeSelectionStarted);

class AHYUpgradeItem;
class UHYMotionControllerComponent;

UCLASS()
class HELLYEAH_API AHYUpgradeSelector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHYUpgradeSelector();

	UFUNCTION(BlueprintCallable)
	void StartUpgradeSelection();

	UFUNCTION(BlueprintCallable)
	void FinishUpgradeSelection(AHYUpgradeItem* UpgradeItem);

	UPROPERTY(BlueprintAssignable)
	FOnUpgradeSelectionStarted OnUpgradeSelectionStarted;

	UPROPERTY(BlueprintAssignable)
	FOnUpgradeSelected OnUpgradeSelected;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ItemsAmount = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 CurveOffset = -40;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer ExcludeTags;

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<AHYUpgradeItem>> UpgradeItems;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AHYUpgradeItem> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ItemSpacing = 200.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
