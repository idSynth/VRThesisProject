// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/MusicSubsystem.h"
#include "Sound/AmbientSound.h"
#include "Components/AudioComponent.h"
#include "Quartz/QuartzSubsystem.h"
#include "Quartz/AudioMixerClockHandle.h"

void UMusicSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Collection.InitializeDependency<UQuartzSubsystem>();

	Super::Initialize(Collection);
}

void UMusicSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UMusicSubsystem::LoadMusicFromDescription(UDAMusicDescription* InMusicDescription)
{
	if (!IsValid(GetWorld()))
	{
		return;
	}

	if (!IsValid(QuartzSubsystem))
	{
		QuartzSubsystem = UQuartzSubsystem::Get(GetWorld());
	}

	if (!IsValid(Clock))
	{
		Clock = QuartzSubsystem->CreateNewClock(this, FName("Main"), FQuartzClockSettings());
	}

	if (!IsValid(SoundActor))
	{
		SoundActor = GWorld->SpawnActor<AAmbientSound>();

		const UHYMusicData* MusicSettings = GetDefault<UHYMusicData>();

		SoundActor->GetAudioComponent()->SetSound(
			MusicSettings->BackgroundMusic.LoadSynchronous());
	}

	ensure(IsValid(SoundActor) && IsValid(Clock));

	MusicDescription = InMusicDescription;

	FQuartzQuantizationBoundary Quantization = FQuartzQuantizationBoundary(EQuartzCommandQuantization::Bar, 1.0f, EQuarztQuantizationReference::TransportRelative);

	TArray<FStemDescription> Stems;
	MusicDescription->Stems.GenerateValueArray(Stems);

	for (const FStemDescription& Stem : Stems)
	{
		SoundActor->GetAudioComponent()->SetWaveParameter(MusicTypeToName[Stem.MusicType], Stem.SoundAsset.LoadSynchronous());
		SoundActor->GetAudioComponent()->SetFloatParameter(MusicTypeToBPMParam[Stem.MusicType], Stem.BPM);
	}

	SoundActor->GetAudioComponent()->SetFloatParameter(FName("BPM"), MusicDescription->GeneralBPM);

	Clock->SetBeatsPerMinute(this, Quantization, FOnQuartzCommandEventBP(), Clock, MusicDescription->GeneralBPM);
	SoundActor->GetAudioComponent()->PlayQuantized(this, Clock, Quantization, FOnQuartzCommandEventBP());
	
	OnMusicSettingsChanged.Broadcast(InMusicDescription);
}
 