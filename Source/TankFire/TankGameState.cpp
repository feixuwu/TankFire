// Fill out your copyright notice in the Description page of Project Settings.

#include "TankGameState.h"
#include "Net/UnrealNetwork.h"

ATankGameState::ATankGameState()
{
	NetUpdateFrequency = 10.0f;

	MaxBulletCount = 5;
	InitBulletCount = 5;
	GameLeftTime = 300;
}

void ATankGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATankGameState, MaxBulletCount);
	DOREPLIFETIME(ATankGameState, InitBulletCount);
	DOREPLIFETIME(ATankGameState, GameLeftTime);
	DOREPLIFETIME(ATankGameState, ColorList);
}

