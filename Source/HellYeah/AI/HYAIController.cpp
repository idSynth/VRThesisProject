// Fill out your copyright notice in the Description page of Project Settings.


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
