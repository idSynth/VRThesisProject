// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.


#include "AI/HYAIController.h"

void AHYAIController::BeginPlay()
{
	Super::BeginPlay();

	if (!DefaultBehaviorTree)
	{
		return;
	}

	RunBehaviorTree(DefaultBehaviorTree);
}
