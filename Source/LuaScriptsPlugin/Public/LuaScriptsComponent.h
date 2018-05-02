// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LuaScriptsComponent.generated.h"

namespace sol {
	class state;
}


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUASCRIPTSPLUGIN_API ULuaScriptsComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	ULuaScriptsComponent();

protected:
	sol::state* state;
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetState(sol::state* newState);
};
