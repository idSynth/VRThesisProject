// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.


#include "Actors/Music/HYGuitarBase.h"
#include "Components/BoxComponent.h"
#include "Components/HYGrabComponent.h"
#include "Components/SplineComponent.h"
#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/HYMotionControllerComponent.h"
#include "Health/HYHealthComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "MetasoundOutput.h"
#include "MetasoundPrimitives.h"
#include "MetasoundTime.h"

#include "HYGameplayTags.h"
#include "HYFunctionLibrary.h"

// Sets default values
AHYGuitarBase::AHYGuitarBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Guitar = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GuitarMesh"));
	Guitar->SetupAttachment(RootComponent);

	StrumHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("StrumHitBox"));
	StrumHitBox->SetupAttachment(Guitar, FName("Strum"));

	StrumGrabComponent = CreateDefaultSubobject<UHYGrabComponent>(TEXT("StrumGrabComponent"));
	StrumGrabComponent->SetupAttachment(StrumHitBox);

	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	Audio->SetupAttachment(StrumHitBox);

	Fretboard = CreateDefaultSubobject<USplineComponent>(TEXT("Fretboard"));
	Fretboard->SetupAttachment(Guitar);

	FretboardHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FretboardHitBox"));
	FretboardHitBox->SetupAttachment(Fretboard);

	FretGrabComponent = CreateDefaultSubobject<UHYGrabComponent>(TEXT("FretGrabComponent"));
	FretGrabComponent->SetupAttachment(FretboardHitBox);

	// Visuals
	FretboardVisuals = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FretboardVisuals"));
	FretboardVisuals->SetupAttachment(FretboardHitBox);

	StrumVisuals = CreateDefaultSubobject<UNiagaraComponent>(TEXT("StrumVisuals"));
	StrumVisuals->SetupAttachment(StrumHitBox);

	NoteName = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NoteName"));
	NoteName->SetupAttachment(FretboardVisuals);
}

// Called when the game starts or when spawned
void AHYGuitarBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHYGuitarBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	CalculateFretboard();
	
	StrumHitBox->SetBoxExtent(FVector(StrumHitBoxExtent));
	StrumHitBox->SetRelativeLocation(FVector::UpVector * StrumHitBoxExtent);
}

void AHYGuitarBase::CalculateFretboard()
{
	if (!Guitar)
	{
		return;
	}

	// Convert to relative space (relative to Guitar)
	const FTransform GuitarTransform = Guitar->GetComponentTransform();
	FVector FretboardStart = GuitarTransform.InverseTransformPosition(Guitar->GetSocketLocation(FName("FretboardStart")));
	FVector FretboardEnd = GuitarTransform.InverseTransformPosition(Guitar->GetSocketLocation(FName("FretboardEnd")));

	Fretboard->ClearSplinePoints();
	Fretboard->AddPoint(FSplinePoint(0.0f, FretboardStart, ESplinePointType::Linear));
	Fretboard->AddPoint(FSplinePoint(1.0f, FretboardEnd, ESplinePointType::Linear));

	FVector Midpoint = (FretboardStart + FretboardEnd) * 0.5f;

	FVector Direction = (FretboardEnd - FretboardStart);
	float Distance = Direction.Size();
	FVector DirectionNormalized = Direction.GetSafeNormal();

	FRotator BoxRotation = DirectionNormalized.Rotation();

	if (!FretboardHitBox)
	{
		return;
	}

	// Set box location and rotation
	FretboardHitBox->SetRelativeLocation(Midpoint);
	FretboardHitBox->SetRelativeRotation(BoxRotation);

	FVector BoxExtent;
	BoxExtent.X = Distance * 0.5f;
	BoxExtent.Y = FretboardWidth * 0.5f;
	BoxExtent.Z = FretboardHeight * 0.5f;

	FretboardHitBox->SetBoxExtent(BoxExtent, false);
}

void AHYGuitarBase::UpdateFretPosition()
{
	FVector SplinePosition = Fretboard->FindLocationClosestToWorldLocation(FretMotionController->GetComponentLocation(), ESplineCoordinateSpace::World);
	
	FretboardVisuals->SetWorldLocation(SplinePosition);
	Audio->SetFloatParameter(FName("NormalizedFretboardPosition"), CalculateFretboardPosition(SplinePosition));
}

void AHYGuitarBase::UpdateStrumming()
{
	// MC stands for MotionController simply for lengthy naming reasons
	FVector LocalMCLocation = StrumHitBox->GetComponentTransform().InverseTransformPosition(StrumMotionController->GetComponentLocation());
	FVector StrumBoxExtent = StrumHitBox->GetUnscaledBoxExtent();
	
	FVector ClampedLocation;
	ClampedLocation.X = FMath::Clamp(LocalMCLocation.X, StrumBoxExtent.X * -1.0f, StrumBoxExtent.X);
	ClampedLocation.Y = FMath::Clamp(LocalMCLocation.Y, StrumBoxExtent.Y * -1.0f, StrumBoxExtent.Y);
	ClampedLocation.Z = FMath::Clamp(LocalMCLocation.Z, StrumBoxExtent.Z * -1.0f, StrumBoxExtent.Z);
	
	StrumVisuals->SetRelativeLocation(ClampedLocation);

	Audio->SetFloatParameter(FName("GaterAmount"), FMath::Clamp(ClampedLocation.Y / 2.0f, 0.0f, 1.0f));
	
	FVector Delta;

	Delta.X = ClampedLocation.X - LocalMCLocation.X;
	Delta.Y = ClampedLocation.Y - LocalMCLocation.Y;
	Delta.Z = ClampedLocation.Z - LocalMCLocation.Z;

	bool bIsHandInsideStrummingBox = !(Delta.X > 0.0f || Delta.Y > 0.0f || Delta.Z > 0.0f);

	float StrummingVelocity = StrumMotionController->GetLinearVelocityPublic().Length();
	float NormalizedStrummingVelocity = UKismetMathLibrary::NormalizeToRange(StrummingVelocity, 0.0f, 150.0f);

	Audio->SetFloatParameter(FName("NormalizedStrummingVelocity"), FMath::Clamp(NormalizedStrummingVelocity, 0.0f, 1.0f));

	//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::White, *FString::SanitizeFloat(StrummingVelocity));

	// at the top of the function
	const float Now = GetWorld()->GetTimeSeconds();
	const float MinInterval = 1.0f / DamageRate;

	if (NormalizedStrummingVelocity > StrumThreshold && Now - LastDamageTime >= MinInterval)
	{
		Audio->SetTriggerParameter(FName("StrummingStart"));

		DealDamage();
		LastDamageTime = Now;
	}
}

void AHYGuitarBase::UpdateNoteName(FName OutputName, const FMetaSoundOutput& MSOutput)
{
	if (!MSOutput.IsValid())
	{
		return;
	}

	float MIDINote;

	if (!MSOutput.Get(MIDINote))
	{
		return;
	}

	NoteName->SetText(FText::FromString(MIDINoteToName(MIDINote).ToString()));

	OnNoteChanged.Broadcast(MIDINote);
}

FName AHYGuitarBase::MIDINoteToName(const float& MIDINote) const
{
	return MIDINoteNames[FMath::RoundToInt32(MIDINote) % 12];
}

float AHYGuitarBase::CalculateFretboardPosition(const FVector& CurrentSplinePosition)
{
	FVector FretboardStart = Fretboard->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
	FVector FretboardEnd = Fretboard->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::World);

	float DistanceAB = FVector::Dist(FretboardStart, FretboardEnd);
	float DistanceAP = FVector::Dist(FretboardStart, CurrentSplinePosition);

	return FMath::Clamp(DistanceAP/DistanceAB, 0.0f, 1.0f);
}

void AHYGuitarBase::DealDamageMusicOutput(FName OutputName, const FMetaSoundOutput& MSOutput)
{
	if (!bIsShooting)
	{
		return;
	}

	if (!MSOutput.IsValid())
	{
		return;
	}
	
	DealDamage();
}

void AHYGuitarBase::DealDamage()
{
	if (!GetInstigatorController())
	{
		UE_LOG(LogTemp, Error, TEXT("No Instigator Controller found for %s!"), *GetNameSafe(this));
		return;
	}

	TArray<FHitResult> Hits;

	APlayerCameraManager* CameraManager = GetInstigatorController<APlayerController>()->PlayerCameraManager;
	FVector CameraLocation = CameraManager->GetCameraLocation();
	FRotator CameraRotation = CameraManager->GetCameraRotation();

	FVector Start = StrumHitBox->GetComponentLocation();

	float ModifiedDamageDistance = DamageDistance;
	ModifyAttribute.Broadcast(TAG_Attribute_Range, ModifiedDamageDistance);

	FVector End = CameraLocation + CameraRotation.Vector() * ModifiedDamageDistance;
	if (!UKismetSystemLibrary::SphereTraceMultiForObjects(this, Start, End, BaseAttackRadius, DamageObjectTypes, false, {}, DebugTraceType, Hits, true))
	{
		return;
	}

	FHYDamageInfo DamageInfo;
	DamageInfo.Damage = BaseDamage;
	DamageInfo.Instigator = GetInstigator();
	DamageInfo.DamageCauser = this;

	for (const FHitResult& Hit : Hits)
	{
		if (Hit.GetActor())
		{
			FHitResult OutHit;
			if (UKismetSystemLibrary::LineTraceSingle(this, Start, Hit.GetActor()->GetActorLocation(), LineOfSightChannel, false, {}, DebugTraceType, OutHit, true))
			{
				continue;
			}

			if (UHYHealthComponent* HealthComponent = Hit.GetActor()->FindComponentByClass<UHYHealthComponent>())
			{
				DamageInfo.HitResult = Hit;

				ModifyAttribute.Broadcast(TAG_Attribute_Damage_Outcoming, DamageInfo.Damage);

				HealthComponent->TryDamage(DamageInfo);
			}
		}
	}
}

void AHYGuitarBase::StartShooting()
{
	bIsShooting = true;
}

void AHYGuitarBase::EndShooting()
{
	bIsShooting = false;
}

// Called every frame
void AHYGuitarBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

