// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameEngine.h"
#include "TankGameEngine.generated.h"

/**
 * 
 */
UCLASS()
class TANKFIRE_API UTankGameEngine : public UGameEngine
{
	GENERATED_BODY()
	
	
public:

	virtual void HandleNetworkFailure(UWorld *World, UNetDriver *NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString) override;
	
};
