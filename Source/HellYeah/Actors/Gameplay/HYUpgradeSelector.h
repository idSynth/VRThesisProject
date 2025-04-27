// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HYUpgradeSelector.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpgradeSelected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpgradeSelectionStarted);

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
	void FinishUpgradeSelection();

	UPROPERTY(BlueprintAssignable)
	FOnUpgradeSelectionStarted OnUpgradeSelectionStarted;

	UPROPERTY(BlueprintAssignable)
	FOnUpgradeSelected OnUpgradeSelected;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
