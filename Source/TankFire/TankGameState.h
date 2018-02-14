// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TankGameState.generated.h"

/**
 * 
 */
UCLASS()
class TANKFIRE_API ATankGameState : public AGameState
{
	GENERATED_BODY()
	
	
public:

	ATankGameState();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	int MaxBulletCount;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	int InitBulletCount;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	float GameLeftTime;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	TArray<FLinearColor> ColorList;
};
