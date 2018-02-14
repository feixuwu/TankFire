// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "HTML5NetworkingPrivate.h"


class FWebSocketNetworkingModule : public IModuleInterface
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FWebSocketNetworkingModule, WebSocketNetworking)

void FWebSocketNetworkingModule::StartupModule()
{
}


void FWebSocketNetworkingModule::ShutdownModule()
{
}

DEFINE_LOG_CATEGORY(LogHTML5Networking);


