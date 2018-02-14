// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WebSocketNetworkConnection.h"
#include "TankWebSocketConnection.generated.h"


/**
 * 
 */
UCLASS()
class WEBSOCKETNETWORKING_API UTankWebSocketConnection : public UWebSocketNetworkConnection
{
	GENERATED_BODY()
	
	
public:

	virtual void CleanUp() override;
	
};

