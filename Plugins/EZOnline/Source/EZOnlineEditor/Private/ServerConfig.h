/*
* EZ-Mobile-Ads - unreal engine 4 ads plugin
*
* Copyright (C) 2017 feiwu <feixuwu@outlook.com> All Rights Reserved.
*/

#pragma once

#include "UObject/NoExportTypes.h"
#include "ServerConfig.generated.h"

/**
 * 
 */
UCLASS(transient, config = Engine)
class UServerConfig : public UObject
{
	GENERATED_BODY()
	
	// if the android admob enable
	UPROPERTY(Config, EditAnywhere,  Meta = (DisplayName = "Center Server for Client"))
	FString CenterServerForClient;

	UPROPERTY(Config, EditAnywhere,  Meta = (DisplayName = "Center Server for Server"))
	FString CenterServerForServer;

	// the banner adunit
	UPROPERTY(Config, EditAnywhere, Meta = (DisplayName = "Override Server Address"))
	FString ServerOverrideAddress;

	UPROPERTY(Config, EditAnywhere, Meta = (DisplayName = "If EZOnline Enable"))
	bool bEnabled;

	UPROPERTY(Config, EditAnywhere, Meta = (DisplayName = "ZoneID"))
	int zoneID;
	
#if WITH_EDITOR
	
	// UObject interface
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
};
