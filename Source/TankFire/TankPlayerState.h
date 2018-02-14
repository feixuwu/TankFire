// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TankPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TANKFIRE_API ATankPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	ATankPlayerState();

	UFUNCTION()
	virtual void OnRep_Invincible();

	UFUNCTION()
	virtual void OnRep_TankColor();

	UFUNCTION(BlueprintImplementableEvent)
	void OnInvincibleChange();

	UFUNCTION(BlueprintImplementableEvent)
	void OnTankColorChange();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	int CurBulletCount;
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	float ResumeTime;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	int DeathCount;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	int KillCount;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, replicatedUsing = OnRep_Invincible)
	bool isInvincible;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, replicatedUsing = OnRep_TankColor)
	FLinearColor TankColor;
};
