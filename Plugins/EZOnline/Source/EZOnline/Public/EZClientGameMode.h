// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "EZClientGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ONLINESUBSYSTEMEZONLINE_API AEZClientGameMode : public AGameMode
{
	GENERATED_BODY()
	
	
public:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void GotoDefaultMap();
	
	UFUNCTION()
	void OnSocketClosed();

	UFUNCTION()
	void OnSocketConnected();

	UFUNCTION()
	void OnSocketConnectFail(const FString& error);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnSocketClosed")
	void K2OnSocketClosed();

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnSocketConnectFail")
	void K2OnSocketConnectFail();

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnSocketConnected")
	void K2OnSocketConnected();
};
