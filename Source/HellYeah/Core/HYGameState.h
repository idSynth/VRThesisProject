// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "HYGameState.generated.h"

UENUM(BlueprintType)
enum class EGamePhase : uint8
{
	Invasion,
	Upgrade,
	Prepare,
	Failed,
	PendingStart
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGamePhaseChanged, EGamePhase, NewGamePhase);

class AHYWaveManager;
class AHYUpgradeSelector;

/**
 * 
 */
UCLASS()
class HELLYEAH_API AHYGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	EGamePhase GetGamePhase() const { return CurrentGamePhase; }

	UFUNCTION(BlueprintCallable)
	EGamePhase GetPreviousGamePhase() const { return PreviousGamePhase; }

	UFUNCTION(BlueprintCallable)
	void SetGamePhase(EGamePhase NewGamePhase);

	UFUNCTION(BlueprintCallable)
	AHYWaveManager* GetWaveManager() const { return WaveManager; }

	UFUNCTION(BlueprintCallable)
	AHYUpgradeSelector* GetUpgradeSelector() const { return UpgradeSelector; }

	UFUNCTION(BlueprintCallable)
	FTimerHandle GetPrepareTimer() const { return PrepareTimerHandle; }

	UPROPERTY(BlueprintAssignable)
	FOnGamePhaseChanged OnGamePhaseChanged;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void HandleWaveEnd(bool bWasSuccessful);

	UFUNCTION()
	void HandleUpgradeSelected(FGameplayTag Tag);

	UFUNCTION()
	void EndPreparePhase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EGamePhase PreviousGamePhase;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EGamePhase CurrentGamePhase;
	
	UPROPERTY()
	TObjectPtr<AHYWaveManager> WaveManager;

	UPROPERTY()
	TObjectPtr<AHYUpgradeSelector> UpgradeSelector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float PrepareTime = 5.0f;

	UPROPERTY()
	FTimerHandle PrepareTimerHandle;
};
