// Fill out your copyright notice in the Description page of Project Settings.

#include "TankLocalPlayer.h"
#include "TankPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "EZOnlineGameInstance.h"

UTankLocalPlayer::UTankLocalPlayer()
{
	PendingLevelPlayerControllerClass = ATankPlayerController::StaticClass();
}

FString UTankLocalPlayer::GetNickname() const
{
	FString SuperName = Super::GetNickname();
	if (SuperName != TEXT("") && SuperName != TEXT("InvalidOSSUser"))
	{
		return SuperName;
	}

	UEZOnlineGameInstance* pGameInstance = Cast<UEZOnlineGameInstance>(UGameplayStatics::GetGameInstance(this) );
	if (pGameInstance == nullptr || pGameInstance->mAccountSaveGame == nullptr)
	{
		return TEXT("GUEST");
	}

	return pGameInstance->mAccountSaveGame->Name;
}