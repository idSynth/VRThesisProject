// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HYCharacter.generated.h"

class UHYHealthComponent;

UCLASS(Abstract)
class HELLYEAH_API AHYCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHYCharacter();

	UFUNCTION(BlueprintCallable, Category = "HYCharacter|Health")
	UHYHealthComponent* GetHealthComponent() const { return HealthComponent; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HYCharacter|Health")
	TObjectPtr<UHYHealthComponent> HealthComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
