// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OnlineSubsystemEZOnline : ModuleRules
{
	public OnlineSubsystemEZOnline(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"EZOnline/Public"
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"EZOnline/Private",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
                "Sockets",
                "WebSocket",
                "OnlineSubsystemUtils",
                "OnlineSubsystem",
            }
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
                "Sockets",
                "EngineSettings"
            }
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

        if (Target.bBuildEditor == true)
        {
            //@TODO: Needed for the triangulation code used for sprites (but only in editor mode)
            //@TOOD: Try to move the code dependent on the triangulation code to the editor-only module
            PrivateDependencyModuleNames.Add("UnrealEd");
        }
    }
}
