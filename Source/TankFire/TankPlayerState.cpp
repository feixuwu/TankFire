// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerState.h"
#include "Net/UnrealNetwork.h"

ATankPlayerState::ATankPlayerState()
{
	NetUpdateFrequency = 10.0f;

	CurBulletCount = 0;
	ResumeTime = 1.5f;
	DeathCount = 0;
	KillCount = 0;
	isInvincible = false;
}

void ATankPlayerState::OnRep_Invincible()
{
	OnInvincibleChange();
}

void ATankPlayerState::OnRep_TankColor()
{
	OnTankColorChange();
}

void ATankPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATankPlayerState, CurBulletCount);
	DOREPLIFETIME(ATankPlayerState, ResumeTime);
	DOREPLIFETIME(ATankPlayerState, DeathCount);
	DOREPLIFETIME(ATankPlayerState, KillCount);
	DOREPLIFETIME(ATankPlayerState, isInvincible);
	DOREPLIFETIME(ATankPlayerState, TankColor);
}
