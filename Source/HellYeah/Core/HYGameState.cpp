// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.


#include "Core/HYGameState.h"
#include "Actors/Gameplay/HYWaveManager.h"
#include "Actors/Gameplay/HYUpgradeSelector.h"
#include "HYFunctionLibrary.h"

void AHYGameState::SetGamePhase(EGamePhase NewGamePhase)
{
	if (NewGamePhase == CurrentGamePhase)
	{
		return;
	}
	
	PreviousGamePhase = CurrentGamePhase;
	CurrentGamePhase = NewGamePhase;

	switch (CurrentGamePhase)
	{
		case EGamePhase::Invasion:
		{
			WaveManager->StartWave();
			break;
		}
		case EGamePhase::Upgrade:
		{
			UpgradeSelector->StartUpgradeSelection();
			break;
		}
		case EGamePhase::Prepare:
		{
			FTimerManagerTimerParameters TimerParams;
			TimerParams.bLoop = false;

			GetWorld()->GetTimerManager().SetTimer(PrepareTimerHandle, this, &AHYGameState::EndPreparePhase, PrepareTime, TimerParams);
			break;
		}
		case EGamePhase::Failed:
		{
			break;
		}
		case EGamePhase::PendingStart:
		{
			break;
		}
	}

	OnGamePhaseChanged.Broadcast(CurrentGamePhase);
}

void AHYGameState::BeginPlay()
{
	Super::BeginPlay();

	WaveManager = UHYFunctionLibrary::GetWaveManager();

	WaveManager->OnWaveEnded.AddDynamic(this, &AHYGameState::HandleWaveEnd);

	UpgradeSelector = UHYFunctionLibrary::GetUpgradeSelector();

	UpgradeSelector->OnUpgradeSelected.AddDynamic(this, &AHYGameState::HandleUpgradeSelected);
}

void AHYGameState::HandleWaveEnd(bool bWasSuccessful)
{
	SetGamePhase(bWasSuccessful ? EGamePhase::Upgrade : EGamePhase::Failed);
}

void AHYGameState::HandleUpgradeSelected(FGameplayTag Tag)
{
	SetGamePhase(EGamePhase::Prepare);
}

void AHYGameState::EndPreparePhase()
{
	if (PreviousGamePhase == EGamePhase::Failed || PreviousGamePhase == EGamePhase::PendingStart)
	{
		WaveManager->ResetWaves();
	}

	SetGamePhase(EGamePhase::Invasion);
}

