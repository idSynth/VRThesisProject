// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "HYStructs.generated.h"

UENUM(BlueprintType)
enum class EListenActor : uint8
{
	Guitar,
	Stage,
	Character
};

UENUM(BlueprintType)
enum class EModifierType : uint8
{
	Increase,
	Decrease
};

UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "HY Project Settings"))
class HELLYEAH_API UHYUpgradesData : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
	TSoftObjectPtr<UDataTable> UpgradesDT;
};

class UHYUpgrade;

USTRUCT(BlueprintType)
struct FHYUpgradeData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Logic)
	TSoftClassPtr<UHYUpgrade> UpgradeClass = TSoftClassPtr<UHYUpgrade>(FSoftClassPath(TEXT("/Script/HellYeah.HYUpgrade")));

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Logic)
	EListenActor ListenTarget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Logic)
	EModifierType ModifierType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Logic, meta = (Categories = "Attribute"))
	FGameplayTag AttributeTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Logic)
	float PercentPerStack = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Visuals)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Visuals)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Visuals)
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Visuals)
	TSoftObjectPtr<UStaticMesh> Mesh;
};
