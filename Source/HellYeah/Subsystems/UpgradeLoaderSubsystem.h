// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "HYStructs.h"
#include "UpgradeLoaderSubsystem.generated.h"

HELLYEAH_API DECLARE_LOG_CATEGORY_EXTERN(LogUpgradeLoader, Log, All);

/**
 * 
 */
UCLASS()
class HELLYEAH_API UUpgradeLoaderSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
	
public:
	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
