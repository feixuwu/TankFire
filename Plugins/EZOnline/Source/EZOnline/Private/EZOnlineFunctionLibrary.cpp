// Fill out your copyright notice in the Description page of Project Settings.

#include "EZOnlineFunctionLibrary.h"
#include "IPAddress.h"
#include "SocketSubsystem.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "OnlineSubsystemTypes.h"
#include "GameFramework/GameMode.h"
#include "EZOnlineGameInstance.h"
#include "Engine.h"

#if PLATFORM_WINDOWS
#include "AllowWindowsPlatformTypes.h"
#endif

#if WITH_EDITOR
#include "Editor.h"
#endif

/*void UEZOnlineFunctionLibrary::SetPlayerUniqueNetId(APlayerController* playerController, const FString& strUniqueNetId)
{
	ULocalPlayer* localPlayer = playerController->GetLocalPlayer();
	localPlayer->SetCachedUniqueNetId(MakeShareable(new FUniqueNetIdString(strUniqueNetId)));
}*/

int UEZOnlineFunctionLibrary::GetWorldPort(const UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	if (!World)
	{
		return 0;
	}

	UGameInstance* pGameInstance = World->GetGameInstance();
	if (pGameInstance)
	{
		FWorldContext* pWorldContext = pGameInstance->GetWorldContext();
		if (pWorldContext->LastURL.Valid)
		{
			return pWorldContext->LastURL.Port;
		}
	}

	return 0;
}

int UEZOnlineFunctionLibrary::GetZoneID(const UObject* WorldContextObject)
{
	UEZOnlineGameInstance* pGameInstance = Cast<UEZOnlineGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject) );
	if (pGameInstance == nullptr)
	{
		return 0;
	}

	return pGameInstance->mAccountSaveGame->ZoneId;
}

void UEZOnlineFunctionLibrary::SetZoneID(const UObject* WorldContextObject, int iZoneID)
{
	UEZOnlineGameInstance* pGameInstance = Cast<UEZOnlineGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
	if (pGameInstance == nullptr)
	{
		return;
	}

	pGameInstance->mAccountSaveGame->ZoneId = iZoneID;

	pGameInstance->SaveAccount();
}

void UEZOnlineFunctionLibrary::RequestExit(const UObject* WorldContextObject, bool force)
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	if (!World)
	{
		return;
	}

	if (GIsEditor)
	{
#if WITH_EDITOR
		GEditor->RequestEndPlayMap();
#endif
	}
	else
	{
		FPlatformMisc::RequestExit(force);
	}
}

FString UEZOnlineFunctionLibrary::GetWorldAddress(const UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	if (!World)
	{
		return TEXT("");
	}

	UGameInstance* pGameInstance = World->GetGameInstance();
	if (pGameInstance)
	{
		FWorldContext* pWorldContext = pGameInstance->GetWorldContext();
		if (pWorldContext->LastURL.Valid)
		{

			//return pWorldContext->LastURL.Port;
		}
	}

	bool bCanBindAll = false;
	TSharedPtr<class FInternetAddr> HostAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(*GLog, bCanBindAll);
	if (HostAddr->IsValid())
	{
		return *HostAddr->ToString(false);
	}

	return TEXT("");
}
