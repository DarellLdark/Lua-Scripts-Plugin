// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "LuaScriptsPlugin.h"
#include "LuaScriptsLibrary.h"

#define LOCTEXT_NAMESPACE "FLuaScriptsPluginModule"

DEFINE_LOG_CATEGORY(LuaScriptsPlugin);

void FLuaScriptsPluginModule::StartupModule()
{
	ULuaScriptsLibrary::Init();
}

void FLuaScriptsPluginModule::ShutdownModule()
{

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLuaScriptsPluginModule, LuaScriptsPlugin)