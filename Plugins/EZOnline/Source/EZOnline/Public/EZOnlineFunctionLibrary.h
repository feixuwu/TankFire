// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EZOnlineFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ONLINESUBSYSTEMEZONLINE_API UEZOnlineFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
public:

	UFUNCTION(BlueprintPure, Category = "EZOnline")
	static int GetWorldPort(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "EZOnline")
	static FString GetWorldAddress(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "EZOnline")
	static void RequestExit(const UObject* WorldContextObject, bool force);

	UFUNCTION(BlueprintCallable, Category = "EZOnline")
	static void SetZoneID(const UObject* WorldContextObject, int iZoneID);

	UFUNCTION(BlueprintCallable, Category = "EZOnline")
	static int GetZoneID(const UObject* WorldContextObject);

	//UFUNCTION(BlueprintCallable, Category = "EZOnline")
	//static void SetPlayerUniqueNetId(APlayerController* playerController, const FString& strUniqueNetId);
	
};
