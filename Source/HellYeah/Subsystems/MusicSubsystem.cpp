// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.


#include "Subsystems/MusicSubsystem.h"
#include "Sound/AmbientSound.h"
#include "Components/AudioComponent.h"
#include "Quartz/QuartzSubsystem.h"
#include "Quartz/AudioMixerClockHandle.h"

void UMusicSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Collection.InitializeDependency<UQuartzSubsystem>();

	Super::Initialize(Collection);

	QuartzCommandEvent.BindDynamic(this, &UMusicSubsystem::OnMusicStarted);
}

void UMusicSubsystem::Deinitialize()
{
	Super::Deinitialize();

	QuartzCommandEvent.Unbind();
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
		Clock->StartClock(this, Clock);
	}

	if (!IsValid(SoundActor))
	{
		SoundActor = GetWorld()->SpawnActor<AAmbientSound>();

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
	SoundActor->GetAudioComponent()->PlayQuantized(this, Clock, Quantization, QuartzCommandEvent);
	
	OnMusicSettingsChanged.Broadcast(InMusicDescription);
}

void UMusicSubsystem::OnMusicStarted(EQuartzCommandDelegateSubType EventType, FName Name)
{
	OnMusicStartedDelegate.Broadcast(EventType, Name);
}
