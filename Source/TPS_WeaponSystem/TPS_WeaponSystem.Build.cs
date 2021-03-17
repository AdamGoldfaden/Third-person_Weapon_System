// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TPS_WeaponSystem : ModuleRules
{
	public TPS_WeaponSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
