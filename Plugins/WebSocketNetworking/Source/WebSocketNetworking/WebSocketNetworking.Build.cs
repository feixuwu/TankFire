// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using System.IO;
using System;

namespace UnrealBuildTool.Rules
{
    public class WebSocketNetworking  : ModuleRules
	{
        private string ModulePath
        {
            get { return ModuleDirectory; }
        }

        public WebSocketNetworking(ReadOnlyTargetRules Target) : base(Target)
		{
            PrivateDependencyModuleNames.AddRange(
                new string[] { 
                    "Core", 
                    "CoreUObject",
                    "Engine",
					"EngineSettings",
                    "ImageCore",
                    "Sockets",
					"PacketHandler",
                    "OpenSSL",
                    "WebSocket",
                    "zlib"
                }
            );

            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                PrivateIncludePaths.Add("WebSocketNetworking/ThirdParty/include/Win64");

                string strStaticPath = Path.GetFullPath(Path.Combine(ModulePath, "ThirdParty/lib/Win64/"));
                PublicLibraryPaths.Add(strStaticPath);


                string[] StaticLibrariesX64 = new string[] {
                "websockets_static.lib",
                };

                foreach (string Lib in StaticLibrariesX64)
                {
                    PublicAdditionalLibraries.Add(Lib);
                }
            }
            else if (Target.Platform == UnrealTargetPlatform.Linux)
            {
                Definitions.Add("PLATFORM_UWP=0");
                PrivateDependencyModuleNames.Add("OpenSSL");
                PrivateIncludePaths.Add("WebSocketNetworking/ThirdParty/include/Linux");
                string strStaticPath = Path.GetFullPath(Path.Combine(ModulePath, "ThirdParty/lib/Linux/"));
                PublicLibraryPaths.Add(strStaticPath);

                string[] StaticLibrariesMac = new string[] {
                "libwebsockets.a",
                 };

                foreach (string Lib in StaticLibrariesMac)
                {
                    PublicAdditionalLibraries.Add(Path.Combine(strStaticPath, Lib));
                }
            }
            else
            {
                PrivateDependencyModuleNames.Add("libWebSockets");
            }

        }
	}
}
