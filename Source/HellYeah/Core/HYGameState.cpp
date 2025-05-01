// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HYGameState.h"
#include "Actors/Gameplay/HYWaveManager.h"
#include "Actors/Gameplay/HYUpgradeSelector.h"
#include "Kismet/GameplayStatics.h"

void AHYGameState::SetGamePhase(EGamePhase NewGamePhase)
{
	if (NewGamePhase == CurrentGamePhase)
	{
		return;
	}

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
	}

	OnGamePhaseChanged.Broadcast(CurrentGamePhase);
}

void AHYGameState::BeginPlay()
{
	Super::BeginPlay();

	WaveManager = Cast<AHYWaveManager>(UGameplayStatics::GetActorOfClass(this, AHYWaveManager::StaticClass()));

	WaveManager->OnWaveEnded.AddDynamic(this, &AHYGameState::HandleWaveEnd);

	UpgradeSelector = Cast<AHYUpgradeSelector>(UGameplayStatics::GetActorOfClass(this, AHYUpgradeSelector::StaticClass()));

	UpgradeSelector->OnUpgradeSelected.AddDynamic(this, &AHYGameState::HandleUpgradeSelected);
}

void AHYGameState::HandleWaveEnd()
{
	SetGamePhase(EGamePhase::Upgrade);
}

void AHYGameState::HandleUpgradeSelected(FGameplayTag Tag)
{
	SetGamePhase(EGamePhase::Prepare);
}

void AHYGameState::EndPreparePhase()
{
	SetGamePhase(EGamePhase::Invasion);
}

