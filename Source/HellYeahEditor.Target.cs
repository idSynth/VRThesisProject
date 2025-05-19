// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class HellYeahEditorTarget : TargetRules
{
	public HellYeahEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "HellYeah" } );
	}
}
