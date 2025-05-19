// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DSP/MidiNoteQuantizer.h"
#include "AudioMixerBlueprintLibrary.h"
#include "DAMusicDescription.generated.h"

UENUM(BlueprintType)
enum class EMusicScale : uint8
{
	// Modes
	Major,
	Minor_Dorian,
	Phrygian,
	Lydian,
	Dominant7th_Mixolydian,
	NaturalMinor_Aeolian,
	HalfDiminished_Locrian,

	// Non-Diatonic
	Chromatic,
	WholeTone,
	DiminishedWholeTone,

	// pentatonic
	MajorPentatonic,
	MinorPentatonic,
	Blues,

	// bebop
	Bebop_Major,
	Bebop_Minor,
	Bebop_MinorNumber2,
	Bebop_Dominant,

	// common major/minors
	HarmonicMajor,
	HarmonicMinor,
	MelodicMinor,
	SixthModeOfHarmonicMinor,

	// lydian/augmented
	LydianAugmented,
	LydianDominant,
	Augmented,

	// diminished
	Diminished,
	Diminished_BeginWithHalfStep,
	Diminished_BeginWithWholeStep,
	HalfDiminished_LocrianNumber2,

	// other
	Spanish_or_Jewish,
	Hindu,

	Count
};

UENUM(BlueprintType)
enum class EMusicType : uint8
{
	Drums,
	Chords,
	Lead
};

USTRUCT(BlueprintType)
struct FStemDescription
{
	GENERATED_BODY()

public:
	FStemDescription()
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music Data")
	EMusicType MusicType = EMusicType::Chords;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Music Data")
	TSoftObjectPtr<USoundWave> SoundAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Music Data")
	int32 BPM = 170;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Music Data", meta = (EditCondition = "MusicType != EMusicType::Drums", EditConditionHides))
	EMusicalNoteName RootNote = EMusicalNoteName::C;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Music Data", meta = (EditCondition = "MusicType != EMusicType::Drums", EditConditionHides))
	EMusicScale Scale = EMusicScale::Major;
};


/**
 * 
 */
UCLASS()
class HELLYEAH_API UDAMusicDescription : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Music Data")
	int32 GeneralBPM;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Music Data")
	TMap<EMusicType, FStemDescription> Stems;
};
