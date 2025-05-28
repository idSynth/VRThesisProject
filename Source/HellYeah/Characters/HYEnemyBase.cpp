// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.


#include "Characters/HYEnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void AHYEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void AHYEnemyBase::Stun(float MovementSpeedMultiplier, float RecoveryTimeMultiplier)
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed * MovementSpeedMultiplier;
	
	GetWorld()->GetTimerManager().SetTimer(StunTimer, this, &AHYEnemyBase::ResetStun, RecoveryTime * RecoveryTimeMultiplier);
}

void AHYEnemyBase::ResetStun()
{
	GetWorld()->GetTimerManager().ClearTimer(StunTimer);
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
}

void AHYEnemyBase::SetDescription(const FHYEnemyDescription& NewDescription)
{
	Description = NewDescription;

	GetMesh()->SetSkeletalMesh(Description.Mesh.LoadSynchronous());
	GetMesh()->SetMaterial(0, Description.Material.LoadSynchronous());

	GetCharacterMovement()->MaxWalkSpeed = Description.MovementSpeed;
	DefaultWalkSpeed = Description.MovementSpeed;

	StartCurrentBehaviorTree();
}

void AHYEnemyBase::StartCurrentBehaviorTree()
{
	GetAIControllerTyped()->RunBehaviorTree(Description.BehaviorTree.LoadSynchronous());
}
