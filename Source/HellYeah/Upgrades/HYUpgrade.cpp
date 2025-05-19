// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.


#include "Upgrades/HYUpgrade.h"
#include "Core/HYPlayerState.h"
#include "Characters/HYCharacter.h"
#include "Characters/HYPlayerBase.h"
#include "Actors/Music/HYGuitarBase.h"
#include "Components/HYInventoryComponent.h"
#include "Interfaces/HYModifierProvider.h"
#include "Actors/Gameplay/HYStage.h"

#include "Kismet/GameplayStatics.h"

AActor* UHYUpgrade::GetListenActor_Implementation()
{
	switch (ListenTarget)
	{
		case EListenActor::Character:
		{
			return GetOwningCharacter();
		}
		case EListenActor::Guitar:
		{
			if (AHYPlayerBase* Player = Cast<AHYPlayerBase>(GetOwningCharacter()))
			{
				return Player->Guitar;
			}
	
			return nullptr;
		}
		case EListenActor::Stage:
		{
			return UGameplayStatics::GetActorOfClass(Owner, AHYStage::StaticClass());
		}
	}

	return nullptr;
}

bool UHYUpgrade::BindModifierDelegate()
{
	if (AActor* Actor = GetListenActor())
	{
		if (IHYModifierProvider* Provider = Cast<IHYModifierProvider>(Actor))
		{
			FModifyAttribute* Delegate = Provider->GetModifierDelegate();
			ModifierDelegateHandle = Delegate->AddUObject(this, &UHYUpgrade::ModifyAttribute);
			return true;
		}
	}

	return false;
}

bool UHYUpgrade::UnbindModifierDelegate()
{
	if (AActor* Actor = GetListenActor())
	{
		if (IHYModifierProvider* Provider = Cast<IHYModifierProvider>(Actor))
		{
			FModifyAttribute* Delegate = Provider->GetModifierDelegate();
			Delegate->Remove(ModifierDelegateHandle);
			return true;
		}
	}

	return false;
}

bool UHYUpgrade::InitializeUpgrade(UHYInventoryComponent* InOwner)
{
	SetOwner(InOwner);

	if (!BindModifierDelegate())
	{
		return false;
	}

	OnInitialized();

	return true;
}

bool UHYUpgrade::UninitializeUpgrade(UHYInventoryComponent* InOwner)
{
	SetOwner(InOwner);
	
	UnbindModifierDelegate();

	OnUninitialized();

	return true;
}

bool UHYUpgrade::Activate()
{
	OnActivated();

	return true;
}

void UHYUpgrade::ModifyAttribute(const FGameplayTag& InAttributeTag, float& Attribute)
{
	if (AttributeTag.MatchesTagExact(InAttributeTag))
	{
		Attribute = ModifyAttributeBP(AttributeTag, Attribute);
	}
}

float UHYUpgrade::ModifyAttributeBP_Implementation(const FGameplayTag& InAttributeTag, const float& Attribute)
{
	return Attribute * GetPercentFromStacks();
}

void UHYUpgrade::SetUpgradeData(const FHYUpgradeData& Data)
{
	AttributeTag = Data.AttributeTag;
	ListenTarget = Data.ListenTarget;
	ModifierType = Data.ModifierType;
	PercentPerStack = Data.PercentPerStack;
}

AHYCharacter* UHYUpgrade::GetOwningCharacter()
{
	if (AHYPlayerState* PlayerState = Cast<AHYPlayerState>(Owner->GetOwner()))
	{
		return Cast<AHYCharacter>(PlayerState->GetPawn());
	}

	return Cast<AHYCharacter>(Owner->GetOwner());
}

float UHYUpgrade::GetPercentFromStacks() const
{
	float ModifierSign = (ModifierType == EModifierType::Increase) ? 1 : -1;
	return 1.0f + (FMath::Max(0, Owner->GetStacksByTag(Tag)) * PercentPerStack * ModifierSign);
}
