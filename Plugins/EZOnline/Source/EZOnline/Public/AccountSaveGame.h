// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AccountSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ONLINESUBSYSTEMEZONLINE_API UAccountSaveGame : public USaveGame
{
	GENERATED_BODY()
	
	
public:

	UPROPERTY(BlueprintReadWrite)
		FString Account;

	UPROPERTY(BlueprintReadWrite)
		FString Name;

	UPROPERTY(BlueprintReadWrite)
		int Segment;

	UPROPERTY(BlueprintReadWrite)
		int Star;

	UPROPERTY(BlueprintReadWrite)
		int ZoneId;

	UPROPERTY(BlueprintReadWrite)
		int Cup;
};
