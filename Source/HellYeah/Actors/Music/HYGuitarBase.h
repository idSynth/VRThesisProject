// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/HYModifierProvider.h"

#include "HYGuitarBase.generated.h"

class UBoxComponent;
class UHYGrabComponent;
class UNiagaraComponent;
class USplineComponent;
class UAudioComponent;
class UTextRenderComponent;
class UHYMotionControllerComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNoteChanged, float, MIDINote);


UCLASS()
class HELLYEAH_API AHYGuitarBase : public AActor, public IHYModifierProvider
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHYGuitarBase();

	FModifyAttribute ModifyAttribute;
	virtual FModifyAttribute* GetModifierDelegate() override { return &ModifyAttribute; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> Guitar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> StrumHitBox;	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> FretboardHitBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UHYGrabComponent> StrumGrabComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UHYGrabComponent> FretGrabComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USplineComponent> Fretboard;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UAudioComponent> Audio;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UHYMotionControllerComponent> FretMotionController;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UHYMotionControllerComponent> StrumMotionController;

	UPROPERTY(BlueprintAssignable)
	FOnNoteChanged OnNoteChanged;

	UFUNCTION(BlueprintCallable)
	FName MIDINoteToName(const float& MIDINote) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UNiagaraComponent> FretboardVisuals;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UNiagaraComponent> StrumVisuals;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UTextRenderComponent> NoteName;

	UFUNCTION(BlueprintCallable)
	void CalculateFretboard();

	UFUNCTION(BlueprintCallable)
	void UpdateFretPosition();

	UFUNCTION(BlueprintCallable)
	void UpdateStrumming();

	UFUNCTION(BlueprintCallable)
	void UpdateNoteName(FName OutputName, const FMetaSoundOutput& MSOutput);

	UFUNCTION(BlueprintCallable)
	float CalculateFretboardPosition(const FVector& CurrentSplinePosition);

	UFUNCTION(BlueprintCallable)
	void DealDamageMusicOutput(FName OutputName, const FMetaSoundOutput& MSOutput);	
	
	UFUNCTION(BlueprintCallable)
	void DealDamage();

	UFUNCTION(BlueprintCallable)
	void StartShooting();

	UFUNCTION(BlueprintCallable)
	void EndShooting();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool bIsShooting = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float FretboardWidth = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float FretboardHeight = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float StrumHitBoxExtent = 1.8f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TArray<TEnumAsByte<EObjectTypeQuery>> DamageObjectTypes;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TEnumAsByte<ETraceTypeQuery> LineOfSightChannel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 DamageDistance = 250;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float BaseDamage = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float DamageRate = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float BaseAttackRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float StrumThreshold = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TEnumAsByte<EDrawDebugTrace::Type> DebugTraceType;

	UPROPERTY()
	TArray<FName> MIDINoteNames = 
	{
		"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
	};

	// timestamp of the last time we dealt damage
	float LastDamageTime = -FLT_MAX;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
