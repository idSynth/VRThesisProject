// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Data/DAMusicDescription.h"
#include "MusicSubsystem.generated.h"

class AAmbientSound;
class UQuartzSubsystem;
class UQuartzClockHandle;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMusicSettingsChanged, UDAMusicDescription*, NewMusicDescription);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMusicStoppedDelegate);

UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "HY Project Settings"))
class HELLYEAH_API UHYMusicData : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
	TSoftObjectPtr<USoundBase> BackgroundMusic;
};

/**
 * 
 */
UCLASS()
class HELLYEAH_API UMusicSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "Music")
	void LoadMusicFromDescription(UDAMusicDescription* InMusicDescription);

	/** Pause the currently playing music by fading out over FadeDuration seconds. */
	UFUNCTION(BlueprintCallable, Category = "Music")
	void StopMusic(float FadeDuration = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "Music")
	UDAMusicDescription* GetMusicDescription() const { return MusicDescription; }

	UPROPERTY(BlueprintAssignable, Category = "Music")
	FOnMusicSettingsChanged OnMusicSettingsChanged;

	UPROPERTY(BlueprintAssignable, Category = "Music")
	FOnQuartzCommandEvent OnMusicStartedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Music")
	FOnMusicStoppedDelegate OnMusicStoppedDelegate;

private:
	UFUNCTION()
	void OnMusicStarted(EQuartzCommandDelegateSubType EventType, FName Name);

	UFUNCTION()
	void OnMusicStopped();

	UPROPERTY()
	TObjectPtr<UDAMusicDescription> MusicDescription;

	TMap<EMusicType, FName> MusicTypeToName = 
	{
		{EMusicType::Drums, FName("Drums")},
		{EMusicType::Chords, FName("Chords")},
		{EMusicType::Lead, FName("Lead")}
	};

	TMap<EMusicType, FName> MusicTypeToBPMParam =
	{
		{EMusicType::Drums, FName("DrumsBPM")},
		{EMusicType::Chords, FName("ChordsBPM")},
		{EMusicType::Lead, FName("LeadBPM")}
	};
	
	UPROPERTY()
	TObjectPtr<UQuartzSubsystem> QuartzSubsystem;
	
	UPROPERTY()
	UQuartzClockHandle* Clock;

	UPROPERTY()
	FOnQuartzCommandEventBP QuartzCommandEvent;

	UPROPERTY()
	TObjectPtr<AAmbientSound> SoundActor;
};
