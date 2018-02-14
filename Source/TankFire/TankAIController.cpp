// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerState.h"
#include "Engine/World.h"
#include "GameFramework/GameMode.h"
#include "TankGameState.h"
#include "TankPlayerController.h"
#include "Kismet/KismetMathLibrary.h"

ATankAIController::ATankAIController()
{
	bWantsPlayerState = true;

	ReliveCalcTime = 0;
	ResumeBulletTimeSum = 0;
	ReliveCountDownTime = 5;
	InvincibleTime = 5;

	InvincibleCalcTime = 0;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	RandomTankColor();
}

void ATankAIController::SetName(const FString& S)
{
	if (PlayerState != nullptr)
	{
		PlayerState->SetPlayerName(S);
	}
}

void ATankAIController::Destroyed()
{
	Super::Destroyed();
}

void ATankAIController::BeginDestroy()
{
	Super::BeginDestroy();
}

void ATankAIController::ReliveCheck(float DeltaSeconds)
{
	if (!bNeedRelive)
	{
		return;
	}

	ReliveCalcTime -= DeltaSeconds;
	if (ReliveCalcTime < 0)
	{
		ReliveCalcTime = 0;
		bNeedRelive = false;
		
		UWorld* World = GetWorld();
		if (World != nullptr && World->GetAuthGameMode() != nullptr)
		{
			World->GetAuthGameMode()->RestartPlayer(this);
		}
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	if (HasAuthority())
	{
		ReliveCheck(DeltaSeconds);
		ResumeBullet(DeltaSeconds);
		processInvincible(DeltaSeconds);
	}
}

void ATankAIController::processInvincible(float DeltaSeconds)
{
	if (GetPawn() == nullptr || GetPawn()->IsPendingKill() || PlayerState == nullptr)
	{
		return;
	}

	ATankPlayerState* tankPlayerState = Cast<ATankPlayerState>(PlayerState);
	if (tankPlayerState == nullptr)
	{
		return;
	}

	if (tankPlayerState->isInvincible == false)
	{
		return;
	}

	InvincibleCalcTime -= DeltaSeconds;
	if (InvincibleCalcTime < 0)
	{
		tankPlayerState->isInvincible = false;
	}
}

void ATankAIController::RandomTankColor()
{
	ATankGameState* pTankGameState = Cast<ATankGameState>(GetWorld()->GetGameState());
	if (pTankGameState == nullptr)
	{
		return;
	}

	if (pTankGameState->ColorList.Num() > 0)
	{
		int iIndex = UKismetMathLibrary::RandomInteger(pTankGameState->ColorList.Num());
		ATankPlayerState* pPlayerState = Cast<ATankPlayerState>(PlayerState);
		if (pPlayerState != nullptr)
		{
			pPlayerState->TankColor = pTankGameState->ColorList[iIndex];
			pTankGameState->ColorList.RemoveAt(iIndex);
		}
	}
}

void ATankAIController::Possess(APawn* aPawn)
{
	// Set Init Bullet
	ATankGameState* pTankGameState = Cast<ATankGameState>(GetWorld()->GetGameState());
	ATankPlayerState* pPlayerState = Cast<ATankPlayerState>(PlayerState);

	if (pTankGameState && pPlayerState)
	{
		pPlayerState->CurBulletCount = pTankGameState->InitBulletCount;
		pPlayerState->isInvincible = true;
		InvincibleCalcTime = InvincibleTime;
	}

	Super::Possess(aPawn);
}

void ATankAIController::ResumeBullet(float DeltaSeconds)
{
	if (GetPawn() == nullptr || GetPawn()->IsPendingKill() || PlayerState == nullptr)
	{
		return;
	}

	ATankPlayerState* tankPlayerState = Cast<ATankPlayerState>(PlayerState);
	if (tankPlayerState == nullptr)
	{
		return;
	}


	ATankGameState* tankGameState = Cast<ATankGameState>(GetWorld()->GetGameState());
	if (tankGameState == nullptr)
	{
		return;
	}

	if (tankPlayerState->CurBulletCount >= tankGameState->MaxBulletCount)
	{
		ResumeBulletTimeSum = 0;
		return;
	}

	ResumeBulletTimeSum += DeltaSeconds;
	if (ResumeBulletTimeSum >= tankPlayerState->ResumeTime)
	{
		ResumeBulletTimeSum -= tankPlayerState->ResumeTime;
		if (tankPlayerState->CurBulletCount < tankGameState->MaxBulletCount)
		{
			tankPlayerState->CurBulletCount = tankPlayerState->CurBulletCount + 1;
		}
	}
}

void ATankAIController::processBeKilled(AController* killer)
{
	ATankPlayerState* selfState = Cast < ATankPlayerState>(PlayerState);
	if (selfState)
	{
		selfState->DeathCount++;
	}

	if (killer != nullptr)
	{
		ATankPlayerState* killerState = Cast<ATankPlayerState>(killer->PlayerState);
		if (killerState != nullptr && killer != this)
		{
			killerState->KillCount++;
		}
	}

	bNeedRelive = true;
	ReliveCalcTime = ReliveCountDownTime;

	if (Cast<ATankPlayerController>(killer) != nullptr)
	{
		(Cast<ATankPlayerController>(killer))->OnNotifyClientKill(PlayerState->PlayerName);
	}
}