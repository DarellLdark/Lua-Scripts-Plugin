// Fill out your copyright notice in the Description page of Project Settings.

#include "LuaScriptsComponent.h"
#include "LuaScriptsPlugin.h"
#include "LuaScriptsLibrary.h"



ULuaScriptsComponent::ULuaScriptsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetComponentTickInterval(1.0f);
}


// Called when the game starts
void ULuaScriptsComponent::BeginPlay()
{
	Super::BeginPlay();
	ULuaScriptsLibrary::RegisterLuaComponent(this);
}


// Called every frame
void ULuaScriptsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void ULuaScriptsComponent::SetState(sol::state* newState) {
	state = newState;
}