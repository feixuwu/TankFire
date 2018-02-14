// Fill out your copyright notice in the Description page of Project Settings.

#include "TankGameEngine.h"
#include "TankPlayerController.h"

void UTankGameEngine::HandleNetworkFailure(UWorld *World, UNetDriver *NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	UE_LOG(LogNet, Log, TEXT("NetworkFailure: %s, Error: '%s'"), ENetworkFailure::ToString(FailureType), *ErrorString);

	if (!NetDriver)
	{
		return;
	}
	

	ATankPlayerController* pTankPlayerController = Cast<ATankPlayerController>(World->GetFirstPlayerController() );
	if (pTankPlayerController != nullptr && pTankPlayerController->IsGameFinish() )
	{
		return;
	}
	
	Super::HandleNetworkFailure(World, NetDriver, FailureType, ErrorString);
}

