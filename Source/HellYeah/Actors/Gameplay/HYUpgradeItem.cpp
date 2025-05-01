// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Gameplay/HYUpgradeItem.h"
#include "Components/HYGrabComponent.h"
#include "Engine/DataTable.h"
#include "HYStructs.h"
#include "Core/HYPlayerState.h"
#include "Components/HYInventoryComponent.h"
#include "Components/SphereComponent.h"

#include "HYFunctionLibrary.h"

// Sets default values
AHYUpgradeItem::AHYUpgradeItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName(TEXT("PhysicsActor"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GrabComponent = CreateDefaultSubobject<UHYGrabComponent>(TEXT("GrabComponent"));
	GrabComponent->SetupAttachment(Mesh);
}

void AHYUpgradeItem::SetUpgradeTag(const FGameplayTag& Tag)
{
	FHYUpgradeData* Row = UpgradeDT->FindRow<FHYUpgradeData>(Tag.GetTagName(), TEXT("SetUpgradeTag()"));

	if (!Row)
	{
		return;
	}

	UpgradeTag = Tag;
	Mesh->SetStaticMesh(Row->Mesh.LoadSynchronous());
}

// Called when the game starts or when spawned
void AHYUpgradeItem::BeginPlay()
{
	Super::BeginPlay();

	GrabComponent->OnGrabbed.AddDynamic(this, &AHYUpgradeItem::OnItemGrabbed);
}

void AHYUpgradeItem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GrabComponent->OnGrabbed.RemoveDynamic(this, &AHYUpgradeItem::OnItemGrabbed);
	
	Super::EndPlay(EndPlayReason);
}

void AHYUpgradeItem::OnItemGrabbed(UHYMotionControllerComponent* MotionController)
{
	if (AHYPlayerState* PlayerState = UHYFunctionLibrary::GetPlayerStateTyped())
	{
		PlayerState->InventoryComponent->AddStack(GetUpgradeTag());
	}

	GrabComponent->TryRelease();

	OnUpgradeItemGrabbed.Broadcast(this);
}

// Called every frame
void AHYUpgradeItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

