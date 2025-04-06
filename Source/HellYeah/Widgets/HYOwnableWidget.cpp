// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/HYOwnableWidget.h"

void UHYOwnableWidget::NativeOnInitialized()
{
	OnWidgetOwnerSet.AddDynamic(this, &UHYOwnableWidget::WidgetOwnerSet);
}

void UHYOwnableWidget::SetWidgetOwner(AActor* NewWidgetOwner)
{
	if (NewWidgetOwner != WidgetOwner)
	{
		WidgetOwner = NewWidgetOwner;

		OnWidgetOwnerSet.Broadcast(WidgetOwner);
	}
}
