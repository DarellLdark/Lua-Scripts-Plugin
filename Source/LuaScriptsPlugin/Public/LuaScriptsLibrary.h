// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define SOL_CHECK_ARGUMENTS 1

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ThirdParty/Sol2/include/sol.hpp"
#include "LuaScriptsLibrary.generated.h"


class ULuaScriptsComponent;


UCLASS()
class LUASCRIPTSPLUGIN_API ULuaScriptsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	static sol::state GlobalLuaState;
	static FString ScriptsDirectory;

	// Component to state binding
	static TMap<ULuaScriptsComponent*, sol::state*> LocalStates;

	public:
		// Used for initialization
		// Called from module startup
		static void Init();


		// Called by LuaComponents after BeginPlay()
		// Used for setting this objects to GLobalLuaState
		static void RegisterLuaComponent(ULuaScriptsComponent* component);


		// Run script scriptName from Scripts Directory
		// Don't forget about *.lua!
		UFUNCTION(BlueprintCallable, Category = "Lua Scripts Plugin")
		static bool RunLuaScript(const FString& scriptName, const ULuaScriptsComponent* component);


		// Sets Scripts Directory inside game folder
		UFUNCTION(BlueprintCallable, Category = "Lua Scripts Plugin|Utility")
		static void SetScriptsDirectory(const FString& path);


		// Returns Scripts Directory
		UFUNCTION(BlueprintPure, Category = "Lua Scripts Plugin|Utility")
		static FORCEINLINE FString GetScriptsDirectory() { return ScriptsDirectory; }


		// Print value in log
		// Used from Lua scripts
		static void LogMessage(const sol::object& value);
};
