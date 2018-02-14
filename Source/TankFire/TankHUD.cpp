// Fill out your copyright notice in the Description page of Project Settings.

#include "TankHUD.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "EngineUtils.h"
#include "TankPlayerState.h"
#include "TankGameState.h"
#include "Engine/Texture2D.h"

ATankHUD::ATankHUD()
{
	HudFont = nullptr;
	DelayTime = 1.0f;
	ScanTimeSume = 0;
	BasicHeight = 70;
}

void ATankHUD::Tick(float DeltaSeconds)
{
	CachePawnList(DeltaSeconds);
}

void ATankHUD::CachePawnList(float DeltaSeconds)
{
	if (PlayerClass == nullptr)
	{
		return;
	}

	ScanTimeSume += DeltaSeconds;
	if (ScanTimeSume < DelayTime)
	{
		return;
	}

	ScanTimeSume -= DelayTime;
	UWorld* pWorld = GetWorld();
	if (pWorld == nullptr)
	{
		return;
	}

	CacheList.Reset();

	for (TActorIterator<AActor> It(pWorld, PlayerClass); It; ++It)
	{
		AActor* Actor = *It;
		if (!Actor->IsPendingKill())
		{
			CacheList.Add(Cast<APawn>(Actor) );
		}
	}
}

void ATankHUD::DrawHUD()
{
	Super::DrawHUD();

	for (auto it = CacheList.CreateIterator(); it; it++)
	{
		APawn* pPawn = *it;
		if (pPawn == nullptr || pPawn->IsPendingKill())
		{
			continue;
		}

		DrawPawnHud(pPawn);
	}
}

void ATankHUD::DrawPawnHud(APawn* pPawn)
{
	if (pPawn == nullptr || pPawn->IsPendingKill())
	{
		return;
	}

	if (pPawn->PlayerState == nullptr)
	{
		return;
	}

	UWorld* pWorld = GetWorld();
	if (pWorld == nullptr)
	{
		return;
	}

	FVector location = pPawn->GetActorLocation();
	FVector screenPos = Project(location);

	if (screenPos.Z <= 0.0f)
	{
		return;
	}

	ATankPlayerState* pTankPlayerState = Cast<ATankPlayerState>(pPawn->PlayerState);
	if (pTankPlayerState == nullptr)
	{
		return;
	}

	ATankGameState* pTankGameState = Cast<ATankGameState>(pWorld->GetGameState() );
	if (pTankGameState == nullptr)
	{
		return;
	}

	// Draw Text
	float outWidth = 0.0f;
	float outHeight = 0.0f;
	GetTextSize(pTankPlayerState->PlayerName, outWidth, outHeight, HudFont);
	DrawText(pTankPlayerState->PlayerName, FLinearColor(0, 1.0f, 0), screenPos.X - outWidth / 2, screenPos.Y - BasicHeight, HudFont);


	// Draw Bullet;
	if (BulletBgTexture == nullptr || BulletTexture == nullptr)
	{
		return;
	}

	float bulletWidth = BulletBgTexture->GetSizeX();
	
	for (int i = 0; i < pTankGameState->MaxBulletCount; i++)
	{
		float xPos = screenPos.X - bulletWidth * pTankGameState->MaxBulletCount/2 + i * bulletWidth;
		float yPos = screenPos.Y - BasicHeight + outHeight;

		if (i < pTankPlayerState->CurBulletCount)
		{
			DrawTextureSimple(BulletTexture, xPos, yPos);
		}
		else
		{
			DrawTextureSimple(BulletBgTexture, xPos, yPos);
		}
	}
}