// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "WebSocketBlueprintLibrary.h"
#include "MessageProto.h"
#include "AccountSaveGame.h"
#include "EZOnlineGameInstance.generated.h"


/**
 * 
 */
UCLASS()
class ONLINESUBSYSTEMEZONLINE_API UEZOnlineGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	void SetCenterSocket(UWebSocketBase* socket);

	UFUNCTION(BlueprintNativeEvent, Category = "EZOnline")
	void OnConnectComplete();

	UFUNCTION(BlueprintNativeEvent, Category = "EZOnline")
	void OnDataReceive(const FString& data);

	UFUNCTION(BlueprintImplementableEvent, Category = "EZOnline")
	void OnPreJoinGame();

	UFUNCTION(BlueprintImplementableEvent, Category = "EZOnline")
	void OnReceiveZoneList(const TArray<UServerZone*>& zoneList);

	UFUNCTION(BlueprintImplementableEvent, Category = "EZOnline")
	void OnReceiveAccountData(UAccountData* accountData);

	UFUNCTION(BlueprintCallable, Category = "EZOnline")
	void RequestJoinGame();

	UFUNCTION(BlueprintCallable, Category = "EZOnline")
	void RequestCancelJoin();

	UFUNCTION(BlueprintCallable, Category = "EZOnline")
	void QueryZoneList();
	
	UFUNCTION(BlueprintCallable, Category = "EZOnline")
	void QueryAccountData();

	UFUNCTION(BlueprintCallable, Category = "EZOnline")
	void SaveAccount();

	UFUNCTION(BlueprintCallable, Category = "EZOnline")
	void LoadAccount();

	void ProcessClientQueue(USC_CMD_CLIENT_REQUEST_QUEUE* scRequestQueue);
	void ProcessJoinGame(USC_CMD_CLIENT_JOIN_GAME* scJoinGame);
	void ProcessQueryZone(USC_CMD_CLIENT_QUERYZONE* scQueryZone);
	

	UPROPERTY(BlueprintReadOnly)
	FString mLocalToken;

	UPROPERTY(BlueprintReadOnly)
	UWebSocketBase* mCenterSocket;

	//UPROPERTY(BlueprintReadOnly)
	//UAccountData* mLocalAccountData;

	UPROPERTY(BlueprintReadWrite)
	UAccountSaveGame* mAccountSaveGame;
};
