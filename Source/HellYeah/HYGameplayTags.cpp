// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.


#include "HYGameplayTags.h"

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Upgrade, "Upgrade", "The base tag for all upgrades");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Upgrade_Stage, "Upgrade.Stage", "The base tag for all Stage upgrades");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Upgrade_Character, "Upgrade.Character", "The base tag for all Character upgrades");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Upgrade_Guitar, "Upgrade.Guitar", "The base tag for all Guitar upgrades");

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Enemy, "Enemy", "The base tag for all Enemy-related things");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Enemy_Type, "Enemy.Type", "The base tag for all Enemy types");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Enemy_Type_Entrance, "Enemy.Type.Entrance", "The base tag for all Enemies that are coming from the main entrance");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Enemy_Type_Backstage, "Enemy.Type.Backstage", "The base tag for all Enemies that are coming from the backstage");

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attribute, "Attribute", "The base tag for all attributes");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attribute_Damage_Incoming, "Attribute.Damage.Incoming", "Incoming Damage");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attribute_Damage_Outcoming, "Attribute.Damage.Outcoming", "Outcoming Damage");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attribute_Speed_Attack, "Attribute.Speed.Attack", "Attack Speed");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attribute_Speed_Movement, "Attribute.Speed.Movement", "Movement Speed");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attribute_RecoveryTime, "Attribute.RecoveryTime", "Recovery Time");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attribute_Range, "Attribute.Range", "Range");