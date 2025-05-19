// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Health/HYHealthComponent.h"
#include "HYDamageableActor.generated.h"

UCLASS()
class HELLYEAH_API AHYDamageableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHYDamageableActor();

	UFUNCTION(BlueprintCallable, Category = "HYDamageableActor|Health")
	UHYHealthComponent* GetHealthComponent() const { return HealthComponent; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HYDamageableActor|Health")
	TObjectPtr<UHYHealthComponent> HealthComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
