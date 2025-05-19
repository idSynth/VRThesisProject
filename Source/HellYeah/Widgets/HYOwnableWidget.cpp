// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.


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
