// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IpConnection.h"
#include "TankIpConnection.generated.h"

/**
 * 
 */
UCLASS()
class TANKFIRE_API UTankIpConnection : public UIpConnection
{
	GENERATED_BODY()
	
	virtual void InitLocalConnection(UNetDriver* InDriver, class FSocket* InSocket, const FURL& InURL, EConnectionState InState, int32 InMaxPacket = 0, int32 InPacketOverhead = 0) override;
	virtual void LowLevelSend(void* Data, int32 CountBytes, int32 CountBits) override;
	
	FURL ConnectUrl;

public:

	virtual void CleanUp() override;
};
