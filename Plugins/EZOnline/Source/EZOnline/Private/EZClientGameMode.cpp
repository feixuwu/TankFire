// Fill out your copyright notice in the Description page of Project Settings.

#include "EZClientGameMode.h"
#include "WebSocketBlueprintLibrary.h"
#include "EZOnline.h"
#include "CoreGlobals.h"
#include "Misc/ConfigCacheIni.h"
#include "EZOnlineGameInstance.h"
#include "GameMapsSettings.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"


void AEZClientGameMode::BeginPlay()
{
	Super::BeginPlay();

	FString strServer;// = TEXT("ws://192.168.1.3:8000");
	if (!GConfig->GetString(TEXT("/Script/EZOnlineEditor.ServerConfig"), TEXT("CenterServerForClient"), strServer, GEngineIni) || strServer.IsEmpty() )
	{
		UE_LOG(EZOnline, Error, TEXT("CenterServer is not valid:%s"), *strServer);
		return;
	}
	
	UWebSocketBase* webSocket = UWebSocketBlueprintLibrary::Connect(strServer);
	UEZOnlineGameInstance* pEzGameInstance = Cast<UEZOnlineGameInstance>(GetGameInstance() );
	if (pEzGameInstance == nullptr)
	{
		UE_LOG(EZOnline, Error, TEXT("Game Instance Must be set to EZOnlineGameInstance") );
		return;
	}

	webSocket->OnClosed.AddDynamic(this, &AEZClientGameMode::OnSocketClosed);
	webSocket->OnConnectError.AddDynamic(this, &AEZClientGameMode::OnSocketConnectFail);
	webSocket->OnConnectComplete.AddDynamic(this, &AEZClientGameMode::OnSocketConnected);
	pEzGameInstance->SetCenterSocket(webSocket);
}

void AEZClientGameMode::OnSocketConnected()
{
	K2OnSocketConnected();
}

void AEZClientGameMode::OnSocketClosed()
{
	K2OnSocketClosed();
}


void AEZClientGameMode::OnSocketConnectFail(const FString& error)
{
	K2OnSocketConnectFail();
}

void AEZClientGameMode::GotoDefaultMap()
{
	FString Error;
	FURL DefaultURL;
	DefaultURL.LoadURLConfig(TEXT("DefaultPlayer"), GGameIni);
	const UGameMapsSettings* GameMapsSettings = GetDefault<UGameMapsSettings>();
	const FString& TextURL = GameMapsSettings->GetGameDefaultMap() + GameMapsSettings->LocalMapOptions;

	UGameplayStatics::OpenLevel(this, UKismetStringLibrary::Conv_StringToName(GameMapsSettings->GetGameDefaultMap() ), true);
}