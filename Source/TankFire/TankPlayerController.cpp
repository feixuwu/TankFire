// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "InitCameraActor.h"
#include "TankPlayerState.h"
#include "TankGameState.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpectatorPawn.h"
#include "Kismet/KismetMathLibrary.h"

ATankPlayerController::ATankPlayerController()
{
	IsDeathCameraSet = false;
	InitCameraClass = AInitCameraActor::StaticClass();
	ResumeBulletTimeSum = 0;
	ReliveCountDownTime = 5;
	InvincibleTime = 5;

	ReliveCalcTime = 0;
	bNeedRelive = false;
	InvincibleCalcTime = 0;
	isGameFinish = false;
}


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	RandomTankColor();
	bShowMouseCursor = true;
}

void ATankPlayerController::CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult)
{
	if (IsDeathCameraSet)
	{
		OutResult.Location = DeathCameraLocation;
		OutResult.Rotation = DeathCameraRotator;
	}
	else
	{
		FindInitCameraViewPoint(OutResult.Location, OutResult.Rotation);
	}
}

void ATankPlayerController::SpawnPlayerCameraManager()
{
	Super::SpawnPlayerCameraManager();
	PlayerCameraManager->bClientSimulatingViewTarget = 1;
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::Super::SetPawn(InPawn);

	// If we have a pawn we need to determine if we should show/hide the player for cinematic mode
	if (GetPawn() && bCinematicMode && bHidePawnInCinematicMode)
	{
		GetPawn()->SetActorHiddenInGame(true);
	}
}

ASpectatorPawn* ATankPlayerController::SpawnSpectatorPawn()
{
	if (!IsDeathCameraSet)
	{
		return nullptr;
	}

	ASpectatorPawn* pSpectatorOrPawn = Super::SpawnSpectatorPawn();
	
	if (pSpectatorOrPawn != nullptr)
	{
		pSpectatorOrPawn->SetActorLocationAndRotation(DeathLocation, DeathRotator);
	}

	return pSpectatorOrPawn;
}

bool ATankPlayerController::IsGameFinish()
{
	return isGameFinish;
}

void ATankPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	ClientGameEnded(EndGameFocus, bIsWinner);
}

void ATankPlayerController::ClientGameEnded_Implementation(class AActor* EndGameFocus, bool bIsWinner)
{
	isGameFinish = true;
	OnGameEnd();
}

void ATankPlayerController::RandomTankColor()
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

void ATankPlayerController::Possess(APawn* aPawn)
{
	if (aPawn != nullptr)
	{
		aPawn->GetRootComponent()->SetWorldRotation(FRotator(0, 0, 0) );
	}

	if (aPawn != nullptr)
	{
		IsDeathCameraSet = false;
	}

	// Set Init Bullet
	ATankGameState* pTankGameState = Cast<ATankGameState>(GetWorld()->GetGameState() );
	ATankPlayerState* pPlayerState = Cast<ATankPlayerState>(PlayerState);

	if (pTankGameState && pPlayerState)
	{
		pPlayerState->CurBulletCount = pTankGameState->InitBulletCount;
		pPlayerState->isInvincible = true;
		InvincibleCalcTime = InvincibleTime;
	}

	StartSpot = nullptr;

	Super::Possess(aPawn);
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (HasAuthority())
	{
		ResumeBullet(DeltaSeconds);
		ReliveCheck(DeltaSeconds);
		processInvincible(DeltaSeconds);
	}
}

void ATankPlayerController::processInvincible(float DeltaSeconds)
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

void ATankPlayerController::ResumeBullet(float DeltaSeconds)
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

void ATankPlayerController::UnPossess()
{
	if (GetPawn() != nullptr && Cast<ACharacter>(GetPawn()) != nullptr)
	{
		UCameraComponent* pCameraComponent = Cast<UCameraComponent>(GetPawn()->GetComponentByClass(UCameraComponent::StaticClass()));
		if (pCameraComponent != nullptr)
		{
			IsDeathCameraSet = true;
			DeathCameraLocation = pCameraComponent->GetComponentLocation();
			DeathCameraRotator = pCameraComponent->GetComponentRotation();

			DeathLocation = GetPawn()->GetActorLocation();
			DeathRotator = GetPawn()->GetActorRotation();
		}
	}

	Super::UnPossess();
}

/*void ATankPlayerController::PawnPendingDestroy(APawn* inPawn)
{
	if (IsInState(NAME_Inactive))
	{
		UE_LOG(LogPath, Log, TEXT("PawnPendingDestroy while inactive %s"), *GetName());
	}

	if (inPawn != GetPawn() )
	{
		return;
	}

	UnPossess();
	ChangeState(NAME_Spectating);

	if (PlayerState == NULL)
	{
		Destroy();
	}
}*/

void ATankPlayerController::GetPlayerViewPoint(FVector& out_Location, FRotator& out_Rotation) const
{
	if (IsInState(NAME_Spectating) && HasAuthority() && !IsLocalController())
	{
		out_Location = LastSpectatorSyncLocation;
		out_Rotation = LastSpectatorSyncRotation;
	}
	else if (PlayerCameraManager != NULL &&
		PlayerCameraManager->CameraCache.TimeStamp > 0.f) // Whether camera was updated at least once)
	{
		PlayerCameraManager->GetCameraViewPoint(out_Location, out_Rotation);
	}
	else
	{
		AActor* TheViewTarget = GetViewTarget();

		if (TheViewTarget != NULL)
		{
			FindInitCameraViewPoint(out_Location, out_Rotation);
		}
		else
		{
			Super::Super::GetPlayerViewPoint(out_Location, out_Rotation);
		}
	}
}

void ATankPlayerController::processBeKilled(AController* killer)
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

	// notify bekilled
	OnNotifyClientBeKilled(killer->PlayerState->PlayerName);

	if (Cast<ATankPlayerController>(killer) != nullptr && killer != this)
	{
		(Cast<ATankPlayerController>(killer))->OnNotifyClientKill(PlayerState->PlayerName);
	}
}

void ATankPlayerController::OnNotifyClientKill_Implementation(const FString& deathName)
{
	K2_NotifyClientKill(deathName);
}

void ATankPlayerController::OnNotifyClientBeKilled_Implementation(const FString& killerName)
{
	K2_NotifyClientBeKilled(killerName);
}

void ATankPlayerController::ReliveCheck(float DeltaSeconds)
{
	if (!bNeedRelive)
	{
		return;
	}

	if (GetWorld()->GetAuthGameMode() == nullptr)
	{
		return;
	}

	if (GetPawn() != nullptr)
	{
		return;
	}

	ReliveCalcTime -= DeltaSeconds;
	if (ReliveCalcTime < 0)
	{
		ReliveCalcTime = 0;
		bNeedRelive = false;
		GetWorld()->GetAuthGameMode()->RestartPlayer(this);
	}
}

void ATankPlayerController::ChangeToSpectatorState()
{
	ChangeState(NAME_Spectating);
}

void ATankPlayerController::FindInitCameraViewPoint(FVector& out_Location, FRotator& out_Rotation) const
{
	UWorld* pWorld = GetWorld();
	if (pWorld == nullptr)
	{
		return;
	}

	if (InitCameraClass == nullptr)
	{
		return;
	}

	TArray<AActor*> initActorList;
	UGameplayStatics::GetAllActorsOfClass(this, InitCameraClass, initActorList);

	if (initActorList.Num() == 0)
	{
		return;
	}
	
	if (initActorList[0] != nullptr && initActorList[0]->GetComponentByClass(UCameraComponent::StaticClass() ) != nullptr)
	{
		AActor* pInitActor = initActorList[0];
		UCameraComponent* pCameraComponent = Cast<UCameraComponent>(initActorList[0]->GetComponentByClass(UCameraComponent::StaticClass()) );

		out_Location = pCameraComponent->GetComponentLocation();
		out_Rotation = pCameraComponent->GetComponentRotation();
	}
}
