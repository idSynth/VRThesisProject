// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "HYStructs.h"
#include "TagLoaderSubsystem.generated.h"

HELLYEAH_API DECLARE_LOG_CATEGORY_EXTERN(LogTagLoader, Log, All);

/**
 * 
 */
UCLASS()
class HELLYEAH_API UTagLoaderSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
	
public:
	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:
	void RegisterAllTags();

	void RegisterTagsFromDataTableRows(UDataTable* DT);
};
