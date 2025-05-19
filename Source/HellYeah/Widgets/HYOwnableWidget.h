// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HYOwnableWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWidgetOwnerSet, AActor*, NewOwner);

/**
 * 
 */
UCLASS(Abstract)
class HELLYEAH_API UHYOwnableWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable)
	AActor* GetWidgetOwner() const { return WidgetOwner; }

	UFUNCTION(BlueprintCallable)
	void SetWidgetOwner(AActor* NewWidgetOwner);

	UPROPERTY(BlueprintAssignable)
	FOnWidgetOwnerSet OnWidgetOwnerSet;

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetOwnerSet(AActor* NewOwner);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "HellYeah|Widgets")
	AActor* WidgetOwner;
};
