// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TankHUD.generated.h"

/**
 * 
 */
UCLASS()
class TANKFIRE_API ATankHUD : public AHUD
{
	GENERATED_BODY()
	
	
public:

	ATankHUD();

	virtual void DrawHUD() override;
	virtual void Tick(float DeltaSeconds) override;

	void CachePawnList(float DeltaSeconds);
	void DrawPawnHud(APawn* pPawn);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFont* HudFont;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DelayTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APawn> PlayerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* BulletBgTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* BulletTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BasicHeight;

	UPROPERTY()
	TArray<APawn*> CacheList;

	float ScanTimeSume;
	
};
