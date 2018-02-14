// Fill out your copyright notice in the Description page of Project Settings.

#include "EZServerGameMode.h"
#include "EZOnlineFunctionLibrary.h"
#include "Kismet/KismetGuidLibrary.h"
#include "EZOnline.h"

AEZServerGameMode::AEZServerGameMode()
{
	mFetchTokenInterval = 2.0f;
	mFetchTokenCountDown = 0.0f;
}

void AEZServerGameMode::BeginPlay()
{
	Super::BeginPlay();

	mServerKey = UKismetGuidLibrary::NewGuid().ToString();

	FString strServer;// = TEXT("ws://192.168.1.3:8000");
	if (!GConfig->GetString(TEXT("/Script/EZOnlineEditor.ServerConfig"), TEXT("CenterServerForServer"), strServer, GEngineIni) || strServer.IsEmpty())
	{
		UE_LOG(EZOnline, Error, TEXT("CenterServer is not valid:%s"), *strServer);
		return;
	}

	mCenterSocket = UWebSocketBlueprintLibrary::Connect(strServer);
	
	{
		FScriptDelegate scriptDelegate;
		scriptDelegate.BindUFunction(this, TEXT("OnConnectComplete"));
		mCenterSocket->OnConnectComplete.Add(scriptDelegate);
	}

	{
		FScriptDelegate scriptDelegate;
		scriptDelegate.BindUFunction(this, TEXT("OnConnectError"));
		mCenterSocket->OnConnectError.Add(scriptDelegate);
	}

	{
		FScriptDelegate scriptDelegate;
		scriptDelegate.BindUFunction(this, TEXT("OnDataReceive"));
		mCenterSocket->OnReceiveData.Add(scriptDelegate);
	}
}

APlayerController* AEZServerGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	UWorld* pWorld = GetWorld();
	if (pWorld == nullptr)
	{
		return nullptr;
	}

	for (TActorIterator<AActor> It(pWorld, PlayerControllerClass); It; ++It)
	{
		APlayerController* pController = Cast<APlayerController>(*It);
		if (pController == nullptr)
		{
			continue;
		}

		if (pController->PlayerState->UniqueId == UniqueId)
		{
			UNetConnection* pConn = Cast<UNetConnection>(pController->Player);
			if (pConn != nullptr)
			{
				pConn->OwningActor = nullptr;
				pConn->CleanUp();
			}

			//CleanUp
			return pController;
		}
	}

	// query user account data
	QueryUserAccountData(UniqueId.ToString() );

	return Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
}

void AEZServerGameMode::QueryUserAccountData(const FString& account)
{
	UCS_CMD_GS_QUERYACCOUNT* pSendObj = NewObject<UCS_CMD_GS_QUERYACCOUNT>();
	pSendObj->cmd = UMessageProtocommandBlueprintLibrary::CMD_GS_QUERYACCOUNT();
	pSendObj->accout = account;

	FString strSendData;
	if (UWebSocketBlueprintLibrary::ObjectToJson(pSendObj, strSendData))
	{
		mCenterSocket->SendText(strSendData);
	}
}

void AEZServerGameMode::UpdateUserAccount(UAccountData* pAccountData)
{
	UCS_CMD_GS_UPDATEACCOUNT* pSendObj = NewObject<UCS_CMD_GS_UPDATEACCOUNT>();
	pSendObj->cmd = UMessageProtocommandBlueprintLibrary::CMD_GS_UPDATEACCOUNT();
	pSendObj->accountData = pAccountData;

	FString strSendData;
	if (UWebSocketBlueprintLibrary::ObjectToJson(pSendObj, strSendData))
	{
		mCenterSocket->SendText(strSendData);
	}
}

void AEZServerGameMode::SendCenterClose()
{
	UCS_CMD_GS_CLOSE* pSendObj = NewObject<UCS_CMD_GS_CLOSE>();
	pSendObj->cmd = UMessageProtocommandBlueprintLibrary::CMD_GS_CLOSE();

	FString strSendData;
	if (UWebSocketBlueprintLibrary::ObjectToJson(pSendObj, strSendData))
	{
		mCenterSocket->SendText(strSendData);
	}
}

void AEZServerGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	FString strAccount = UGameplayStatics::ParseOption(Options, TEXT("account"));
	FString strToken = UGameplayStatics::ParseOption(Options, TEXT("token"));

	for (int i = 0; i < mUserList.Num(); i++)
	{
		if (mUserList[i]->account == strAccount && mUserList[i]->token == strToken)
		{
			return;
		}
	}

	ErrorMessage = TEXT("Invalid User");
}

void AEZServerGameMode::OnConnectError_Implementation(const FString& strError)
{
	UEZOnlineFunctionLibrary::RequestExit(this, false);
}

void AEZServerGameMode::ProcessGameResult_Implementation()
{
	
}

void AEZServerGameMode::OnDataReceive_Implementation(const FString& data)
{
	int iCmd = 0;
	if (!UWebSocketBlueprintLibrary::GetJsonIntField(data, TEXT("cmd"), iCmd))
	{
		return;
	}

	if (iCmd == UMessageProtocommandBlueprintLibrary::CMD_GS_FETCH_USERTOKEN() )
	{
		USC_CMD_GS_FETCH_USERTOKEN* pScFetchToken = Cast<USC_CMD_GS_FETCH_USERTOKEN>(UWebSocketBlueprintLibrary::JsonToObject(data, USC_CMD_GS_FETCH_USERTOKEN::StaticClass(), false));
		ProcesFetchUserToken(pScFetchToken);
	}
	else if (iCmd == UMessageProtocommandBlueprintLibrary::CMD_GS_ADD_USER())
	{
		USC_CMD_GS_ADD_USER* pScAddUser = Cast<USC_CMD_GS_ADD_USER>(UWebSocketBlueprintLibrary::JsonToObject(data, USC_CMD_GS_ADD_USER::StaticClass(), false));
		ProcessAddUser(pScAddUser);
	}
	else if (iCmd == UMessageProtocommandBlueprintLibrary::CMD_GS_QUERYACCOUNT())
	{
		USC_CMD_GS_QUERYACCOUNT* pScAddUser = Cast<USC_CMD_GS_QUERYACCOUNT>(UWebSocketBlueprintLibrary::JsonToObject(data, USC_CMD_GS_QUERYACCOUNT::StaticClass(), false));
		ProcessUserAccountData(pScAddUser);
	}
}

void AEZServerGameMode::ProcessUserAccountData(USC_CMD_GS_QUERYACCOUNT* pScMsg)
{
	if (pScMsg->result == UMessageProtoenResultBlueprintLibrary::enResult_OK())
	{
		mUserAccountList.Add(pScMsg->accountData->account, pScMsg->accountData);
	}
}

void AEZServerGameMode::ProcesFetchUserToken(USC_CMD_GS_FETCH_USERTOKEN* pScMsg)
{
	if (pScMsg->result == UMessageProtoenResultBlueprintLibrary::enResult_OK())
	{
		mUserList = pScMsg->userList;
	}
}

void AEZServerGameMode::ProcessAddUser(USC_CMD_GS_ADD_USER* pScMsg)
{
	mUserList.Add(pScMsg->newUser);
}

void AEZServerGameMode::OnConnectComplete_Implementation()
{
	FetchUserToken();
}

void AEZServerGameMode::FetchUserToken()
{
	UCS_CMD_GS_FETCH_USERTOKEN* pSendObj = NewObject<UCS_CMD_GS_FETCH_USERTOKEN>();
	pSendObj->cmd = UMessageProtocommandBlueprintLibrary::CMD_GS_FETCH_USERTOKEN();
	pSendObj->serverKey = mServerKey;
	pSendObj->host = UEZOnlineFunctionLibrary::GetWorldAddress(this);
	pSendObj->port = UEZOnlineFunctionLibrary::GetWorldPort(this);

	// override server address
	FString strOverrideAddress;
	if (GConfig->GetString(TEXT("/Script/EZOnlineEditor.ServerConfig"), TEXT("ServerOverrideAddress"), strOverrideAddress, GEngineIni) && !strOverrideAddress.IsEmpty())
	{
		pSendObj->host = strOverrideAddress;
	}

	int32 zoneID = 0;// = TEXT("ws://192.168.1.3:8000");
	if (!GConfig->GetInt(TEXT("/Script/EZOnlineEditor.ServerConfig"), TEXT("zoneID"), zoneID, GEngineIni))
	{
		UE_LOG(EZOnline, Error, TEXT("did not configure zoneid"));
		return;
	}

	pSendObj->zone = zoneID;

	FString strSendData;
	if (UWebSocketBlueprintLibrary::ObjectToJson(pSendObj, strSendData))
	{
		mCenterSocket->SendText(strSendData);
	}
}

void AEZServerGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	mFetchTokenCountDown += DeltaSeconds;
	if (mFetchTokenCountDown > mFetchTokenInterval && (mUserList.Num() == 0) )
	{
		mFetchTokenCountDown = 0;
		FetchUserToken();
	}
}


