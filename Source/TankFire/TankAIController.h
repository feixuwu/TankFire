// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKFIRE_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;
public:

	ATankAIController();

	virtual void Destroyed() override;
	virtual void BeginDestroy() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Possess(APawn* aPawn) override;

	void processBeKilled(AController* killer);
	void processInvincible(float DeltaSeconds);
	void RandomTankColor();

	UFUNCTION(BlueprintCallable)
	void SetName(const FString& S);

	void ResumeBullet(float DeltaSeconds);
	void ReliveCheck(float DeltaSeconds);

	UPROPERTY(EditAnywhere, NoClear, BlueprintReadWrite)
	float ReliveCountDownTime;

	UPROPERTY(EditAnywhere, NoClear, BlueprintReadWrite, Category = Classes)
	float InvincibleTime;

	float ResumeBulletTimeSum;
	float ReliveCalcTime;
	bool bNeedRelive;
	
	float InvincibleCalcTime;
};
