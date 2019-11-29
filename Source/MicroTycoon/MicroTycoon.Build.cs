// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class MicroTycoon : ModuleRules
{
	public MicroTycoon(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(
            new string[] { 
                "Core", 
                "CoreUObject", 
                "Engine", 
                "InputCore" 
        });

		PrivateDependencyModuleNames.AddRange(
            new string[] { 
                "SlateCore", 
                "Slate", 
                "UMG" 
        });

        PublicIncludePaths.AddRange(
            new string[] {
                "MicroTycoon/Public",
        });
    }
}
