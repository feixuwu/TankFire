// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LocalPlayer.h"
#include "TankLocalPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TANKFIRE_API UTankLocalPlayer : public ULocalPlayer
{
	GENERATED_BODY()
	
public:

	UTankLocalPlayer();
	
	virtual FString GetNickname() const override;
};
