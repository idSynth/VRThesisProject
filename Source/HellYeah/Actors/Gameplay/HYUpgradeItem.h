// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "HYUpgradeItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpgradeItemGrabbed, AHYUpgradeItem*, Item);

class UHYGrabComponent;
class UHYMotionControllerComponent;
class USphereComponent;

UCLASS()
class HELLYEAH_API AHYUpgradeItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHYUpgradeItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UHYGrabComponent> GrabComponent;

	UFUNCTION(BlueprintCallable)
	FGameplayTag GetUpgradeTag() const { return UpgradeTag; }

	UFUNCTION(BlueprintCallable)
	void SetUpgradeTag(const FGameplayTag& Tag);

	UPROPERTY(BlueprintAssignable)
	FOnUpgradeItemGrabbed OnUpgradeItemGrabbed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag UpgradeTag;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> UpgradeDT;

	UFUNCTION()
	void OnItemGrabbed(UHYMotionControllerComponent* MotionController);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
