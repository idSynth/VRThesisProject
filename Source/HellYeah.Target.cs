// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class HellYeahTarget : TargetRules
{
	public HellYeahTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "HellYeah" } );
	}
}
