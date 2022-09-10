// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LT_HW3C : ModuleRules
{
	public LT_HW3C(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
