// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
using System.IO;
using UnrealBuildTool;

public class LuaScriptsPlugin : ModuleRules
{

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "ThirdParty/")); }
    }


    public LuaScriptsPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bEnableExceptions = true;

        PublicIncludePaths.AddRange(
            new string[] {
                "LuaScriptsPlugin/Public",
            }
            );


            PrivateIncludePaths.AddRange(
			new string[] {
				"LuaScriptsPlugin/Private",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
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
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);


        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "Sol2", "include"));
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "Lua", "include"));
            PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "Lua", "lib", "lua53.x64.lib"));
        }

    }
}
