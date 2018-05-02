// Fill out your copyright notice in the Description page of Project Settings.

#include "LuaScriptsLibrary.h"
#include "LuaScriptsPlugin.h"
#include "LuaScriptsComponent.h"
#include "Runtime/Core/Public/Misc/Paths.h"


sol::state ULuaScriptsLibrary::GlobalLuaState;

FString ULuaScriptsLibrary::ScriptsDirectory = FPaths::GameDir() + "Scripts/";

TMap<ULuaScriptsComponent*, sol::state*> ULuaScriptsLibrary::LocalStates;


// Used for initialization
// Called from module startup
void ULuaScriptsLibrary::Init() 
{
	GlobalLuaState.open_libraries(sol::lib::base);
}


// Called by LuaComponents after BeginPlay()
// Used for setting this objects to GlobalLuaState
void ULuaScriptsLibrary::RegisterLuaComponent(ULuaScriptsComponent* component) 
{
	sol::state* state = new sol::state();
	state->new_usertype<ULuaScriptsComponent>("LuaAPI");
	state->set("bot", component);
	state->set("LogMessage", &LogMessage);
	component->SetState(state);
	LocalStates.Add(component, state);
}


// Sets Scripts Directory inside game folder
// Allows set up your Scripts Directory in game directory: <YOUR_PROJECT_DIR>/path
void ULuaScriptsLibrary::SetScriptsDirectory(const FString& path) 
{
	ScriptsDirectory = (path[path.Len() - 1] != '/') ? FPaths::GameDir() + path + '/' : FPaths::GameDir() + path;
}


 // Run script scriptName from Scripts Directory
 // Don't forget about *.lua!
bool ULuaScriptsLibrary::RunLuaScript(const FString& scriptName, const ULuaScriptsComponent* component) 
{
	FString script = scriptName.Contains(".lua") ? scriptName : scriptName + ".lua";
	//Error handling
	sol::load_result compileResult = LocalStates[component]->load_file(TCHAR_TO_ANSI(*(ScriptsDirectory + script)));
	if (!compileResult.valid()) 
	{
		UE_LOG(LuaScriptsPlugin, Error, TEXT("Script compilation error!"));
		return false;
	} else 
	{
		auto runResult = LocalStates[component]->script_file(TCHAR_TO_ANSI(*(ScriptsDirectory + script)), [](lua_State*, sol::protected_function_result pfr) {
			sol::error err = pfr;
			UE_LOG(LuaScriptsPlugin, Error, TEXT("Script running error!\n%s"), *FString(err.what()));
			return pfr;
		});
		return runResult.valid();
	}
}

// Print value in log
// Used from Lua scripts
void ULuaScriptsLibrary::LogMessage(const sol::object& value) 
{
	if (value.valid()) {
		switch (value.get_type()) {
			
			case sol::type::boolean:
				UE_LOG(LuaScriptsPlugin, Warning, TEXT("VALUE: %s"), ((value.as<bool>() == true) ? TEXT("TRUE") : TEXT("FALSE")));
				break;
			case sol::type::number:
				UE_LOG(LuaScriptsPlugin, Warning, TEXT("VALUE %f"), value.as<float>());
				break;
			case sol::type::string:
				UE_LOG(LuaScriptsPlugin, Warning, TEXT("VALUE: %s"), *FString(value.as<const char*>()));
				break;
			case sol::type::table:
				UE_LOG(LuaScriptsPlugin, Warning, TEXT("VALUE IS TABLE"));
				break;
			case sol::type::nil:
				UE_LOG(LuaScriptsPlugin, Warning, TEXT("VALUE IS NIL"));
				break;
			default:
				UE_LOG(LuaScriptsPlugin, Warning, TEXT("CAN'T RECOGNIZE TYPE"));
		}
	}
}