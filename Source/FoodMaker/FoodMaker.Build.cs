// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FoodMaker : ModuleRules
{
	public FoodMaker(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new [] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG" });
		
		PublicDependencyModuleNames.AddRange(new[] { "Slate", "SlateCore" });
	}
}
