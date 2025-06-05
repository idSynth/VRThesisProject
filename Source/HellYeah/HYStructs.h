// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "BehaviorTree\BehaviorTree.h"
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

UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "HY Tag Data"))
class HELLYEAH_API UHYTagData : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
	TArray<TSoftObjectPtr<UDataTable>> TagsDT;
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
	EListenActor ListenTarget = EListenActor::Character;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Logic)
	EModifierType ModifierType = EModifierType::Increase;
	
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

class UBehaviorTree;
class AHYEnemyBase;

USTRUCT(BlueprintType)
struct FHYEnemyDescription : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Behavior)
	TSoftClassPtr<AHYEnemyBase> Class = TSoftClassPtr<AHYEnemyBase>(FSoftClassPath(TEXT("/Game/Blueprints/AI/BP_EnemyBase.BP_EnemyBase_C")));;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Behavior)
	TSoftObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Behavior)
	float MovementSpeed = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Behavior)
	float MaxHealth = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Visuals)
	TSoftObjectPtr<USkeletalMesh> Mesh = TSoftObjectPtr<USkeletalMesh>(FSoftObjectPath(TEXT("/Game/Art/Characters/Enemy/SKM_Enemy.SKM_Enemy")));

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Visuals)
	TSoftObjectPtr<UMaterialInterface> Material = TSoftObjectPtr<UMaterialInterface>(FSoftObjectPath(TEXT("/Game/Art/Characters/Enemy/MI_Enemy.MI_Enemy")));

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Visuals)
	float Scale = 1.0f;
};
