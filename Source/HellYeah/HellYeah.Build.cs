// Copyright (c) 2025, idSynth, Michael Ivanov. All rights reserved.

using UnrealBuildTool;

public class HellYeah : ModuleRules
{
	public HellYeah(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.AddRange(new string[]
		{
            "HellYeah"
		});

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "GameplayTags", "AudioMixer", "DeveloperSettings", "Niagara", 
			"HeadMountedDisplay", "MetasoundEngine", "MetasoundFrontend" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
