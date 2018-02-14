// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "WebSocketBlueprintLibrary.h"
#include "MessageProto.h"
#include "EZServerGameMode.generated.h"



/**
 * 
 */
UCLASS()
class ONLINESUBSYSTEMEZONLINE_API AEZServerGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	AEZServerGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	UFUNCTION(BlueprintNativeEvent, Category = "EZOnline")
		void OnConnectComplete();

	UFUNCTION(BlueprintNativeEvent, Category = "EZOnline")
		void OnConnectError(const FString& strError);

	UFUNCTION(BlueprintNativeEvent, Category = "EZOnline")
		void OnDataReceive(const FString& data);

	UFUNCTION(BlueprintNativeEvent, Category = "EZOnline")
		void ProcessGameResult();


	void FetchUserToken();
	void ProcesFetchUserToken(USC_CMD_GS_FETCH_USERTOKEN* pScMsg);
	void ProcessAddUser(USC_CMD_GS_ADD_USER* pScMsg);
	void QueryUserAccountData(const FString& account);
	void ProcessUserAccountData(USC_CMD_GS_QUERYACCOUNT* pScMsg);
	void UpdateUserAccount(UAccountData* pAccountData);
	void SendCenterClose();

	UPROPERTY(BlueprintReadOnly)
		UWebSocketBase* mCenterSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float mFetchTokenInterval;

	UPROPERTY(BlueprintReadOnly)
	FString mServerKey;

	UPROPERTY(BlueprintReadOnly)
		TArray<UUserTokenInfo*> mUserList;

	UPROPERTY()
	TMap<FString, UAccountData*> mUserAccountList;

	float mFetchTokenCountDown;
};
