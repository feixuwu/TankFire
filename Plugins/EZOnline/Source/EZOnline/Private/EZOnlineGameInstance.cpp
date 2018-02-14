// Fill out your copyright notice in the Description page of Project Settings.

#include "EZOnlineGameInstance.h"
#include "EZOnline.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetGuidLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSubsystemTypes.h"
#include "Engine.h"
#include "Net/OnlineEngineInterface.h"

#define ANONYMOUSLY_SAVE	TEXT("AnonymouslySAVE")

void UEZOnlineGameInstance::SetCenterSocket(UWebSocketBase* socket)
{
	if (mCenterSocket != nullptr)
	{
		UWebSocketBase* tmp = mCenterSocket;
		mCenterSocket = nullptr;
		tmp->Close();
	}
	
	mCenterSocket = socket;
	
	{
		FScriptDelegate scriptDelegate;
		scriptDelegate.BindUFunction(this, TEXT("OnConnectComplete"));
		mCenterSocket->OnConnectComplete.Add(scriptDelegate);
	}
	{
		FScriptDelegate scriptDelegate;
		scriptDelegate.BindUFunction(this, TEXT("OnDataReceive"));
		mCenterSocket->OnReceiveData.Add(scriptDelegate);
	}
	
}

void UEZOnlineGameInstance::RequestJoinGame()
{
	UCS_CMD_CLIENT_REQUEST_QUEUE* pSendObj = NewObject<UCS_CMD_CLIENT_REQUEST_QUEUE>();
	pSendObj->cmd = UMessageProtocommandBlueprintLibrary::CMD_CLIENT_REQUEST_QUEUE();

	ULocalPlayer* LocalPlayer = GEngine->GetFirstGamePlayer(GetWorld() );
	if (LocalPlayer == nullptr)
	{
		return;
	}

	pSendObj->userInfo->account = mAccountSaveGame->Account;
	pSendObj->userInfo->name = mAccountSaveGame->Name;
	pSendObj->userInfo->headurl = TEXT("");
	pSendObj->zoneId = mAccountSaveGame->ZoneId;

	FString strSendData;
	if (UWebSocketBlueprintLibrary::ObjectToJson(pSendObj, strSendData) )
	{
		mCenterSocket->SendText(strSendData);
	}
}

void UEZOnlineGameInstance::QueryZoneList()
{
	UCS_CMD_CLIENT_QUERYZONE* pSendObj = NewObject<UCS_CMD_CLIENT_QUERYZONE>();
	pSendObj->cmd = UMessageProtocommandBlueprintLibrary::CMD_CLIENT_QUERYZONE();

	FString strSendData;
	if (UWebSocketBlueprintLibrary::ObjectToJson(pSendObj, strSendData))
	{
		mCenterSocket->SendText(strSendData);
	}
}

void UEZOnlineGameInstance::QueryAccountData()
{
	UCS_CMD_CLIENT_QUERYACCOUNT* pSendObj = NewObject<UCS_CMD_CLIENT_QUERYACCOUNT>();
	pSendObj->cmd = UMessageProtocommandBlueprintLibrary::CMD_CLIENT_QUERYACCOUNT();

	pSendObj->account = mAccountSaveGame->Account;
	pSendObj->name = mAccountSaveGame->Name;

	FString strSendData;
	if (UWebSocketBlueprintLibrary::ObjectToJson(pSendObj, strSendData))
	{
		mCenterSocket->SendText(strSendData);
	}
}

void UEZOnlineGameInstance::RequestCancelJoin()
{
	UCS_CMD_CLIENT_CANCEL_QUEUE* pSendObj = NewObject<UCS_CMD_CLIENT_CANCEL_QUEUE>();
	pSendObj->cmd = UMessageProtocommandBlueprintLibrary::CMD_CLIENT_CANCEL_QUEUE();

	FString strSendData;
	if (UWebSocketBlueprintLibrary::ObjectToJson(pSendObj, strSendData))
	{
		mCenterSocket->SendText(strSendData);
	}
}

void UEZOnlineGameInstance::OnDataReceive_Implementation(const FString& data)
{
	int iCmd = 0;
	if (!UWebSocketBlueprintLibrary::GetJsonIntField(data, TEXT("cmd"), iCmd))
	{
		return;
	}

	if (iCmd == UMessageProtocommandBlueprintLibrary::CMD_CLIENT_REQUEST_QUEUE())
	{
		USC_CMD_CLIENT_REQUEST_QUEUE* pScRequestQueue = Cast<USC_CMD_CLIENT_REQUEST_QUEUE>(UWebSocketBlueprintLibrary::JsonToObject(data, USC_CMD_CLIENT_REQUEST_QUEUE::StaticClass(), false) );
		ProcessClientQueue(pScRequestQueue);
	}
	else if (iCmd == UMessageProtocommandBlueprintLibrary::CMD_CLIENT_JOIN_GAME())
	{
		USC_CMD_CLIENT_JOIN_GAME* pScJoinGame = Cast<USC_CMD_CLIENT_JOIN_GAME>(UWebSocketBlueprintLibrary::JsonToObject(data, USC_CMD_CLIENT_JOIN_GAME::StaticClass(), false));
		ProcessJoinGame(pScJoinGame);
	}
	else if (iCmd == UMessageProtocommandBlueprintLibrary::CMD_CLIENT_QUERYZONE())
	{
		USC_CMD_CLIENT_QUERYZONE* pScQueryZone = Cast<USC_CMD_CLIENT_QUERYZONE>(UWebSocketBlueprintLibrary::JsonToObject(data, USC_CMD_CLIENT_QUERYZONE::StaticClass(), false));
		ProcessQueryZone(pScQueryZone);
	}
	else if (iCmd == UMessageProtocommandBlueprintLibrary::CMD_CLIENT_QUERYACCOUNT())
	{
		USC_CMD_CLIENT_QUERYACCOUNT* pScQueryAccount = Cast<USC_CMD_CLIENT_QUERYACCOUNT>(UWebSocketBlueprintLibrary::JsonToObject(data, USC_CMD_CLIENT_QUERYACCOUNT::StaticClass(), false));
		//mLocalAccountData = pScQueryAccount->accountData;
		SaveAccount();

		OnReceiveAccountData(pScQueryAccount->accountData);
	}
	/*else if (iCmd == UMessageProtocommandBlueprintLibrary::CMD_CLIENT_EMOTION())
	{
		
	}*/
}

void UEZOnlineGameInstance::ProcessQueryZone(USC_CMD_CLIENT_QUERYZONE* scQueryZone)
{
	OnReceiveZoneList(scQueryZone->zoneList);
}

void UEZOnlineGameInstance::LoadAccount()
{
	if (UGameplayStatics::DoesSaveGameExist(TEXT("SaveAccount"), 0))
	{
		mAccountSaveGame = Cast<UAccountSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveAccount"), 0) );
	}
	else
	{
		mAccountSaveGame = NewObject<UAccountSaveGame>();

		mAccountSaveGame->Account = UKismetGuidLibrary::NewGuid().ToString();
		mAccountSaveGame->Name = FString::Printf(TEXT("Guest%d"), UKismetMathLibrary::RandomInteger(1000) + 1);// TEXT("");
		mAccountSaveGame->Segment = 0;
		mAccountSaveGame->Star = 0;		
		mAccountSaveGame->Cup = 0;
		mAccountSaveGame->ZoneId = 0;
	}

	// save UniqueId
	ULocalPlayer* LocalPlayer = GEngine->GetFirstGamePlayer(GetWorld());
	if (LocalPlayer != nullptr)
	{
		LocalPlayer->SetCachedUniqueNetId(MakeShareable(new FUniqueNetIdString(mAccountSaveGame->Account) ) );
	}
}

void UEZOnlineGameInstance::SaveAccount()
{
	TSharedPtr<const FUniqueNetId>sharedUniqueId = UOnlineEngineInterface::Get()->GetUniquePlayerId(GetWorld(), 0);
	if (sharedUniqueId.IsValid())
	{
		mAccountSaveGame->Account = sharedUniqueId->ToString();
	}

	ULocalPlayer* LocalPlayer = GEngine->GetFirstGamePlayer(GetWorld());
	if (LocalPlayer != nullptr)
	{
		FString strNickName = LocalPlayer->GetNickname();
		if (!strNickName.IsEmpty() && strNickName != TEXT("InvalidOSSUser") )
		{
			mAccountSaveGame->Name = strNickName;
		}
	}

	UGameplayStatics::SaveGameToSlot(mAccountSaveGame, TEXT("SaveAccount"), 0);
}


void UEZOnlineGameInstance::ProcessJoinGame(USC_CMD_CLIENT_JOIN_GAME* scJoinGame)
{
	OnPreJoinGame();

	FString strAccount = mAccountSaveGame->Account;
	FString strRemoteMap = FString::Printf(TEXT("%s:%d"), *(scJoinGame->host), scJoinGame->port);
	FString strOption = FString::Printf(TEXT("?account=%s?token=%s"), *strAccount, *mLocalToken);
	UGameplayStatics::OpenLevel(this, UKismetStringLibrary::Conv_StringToName(strRemoteMap), true, strOption);
}

void UEZOnlineGameInstance::ProcessClientQueue(USC_CMD_CLIENT_REQUEST_QUEUE* scRequestQueue)
{
	if (scRequestQueue->result == UMessageProtoenResultBlueprintLibrary::enResult_OK())
	{
		mLocalToken = scRequestQueue->token;
		mAccountSaveGame->ZoneId = scRequestQueue->zoneId;
	}
}

void UEZOnlineGameInstance::OnConnectComplete_Implementation()
{
	UE_LOG(EZOnline, Error, TEXT("Connect CenterServer Socket Finish!!!") );
}

