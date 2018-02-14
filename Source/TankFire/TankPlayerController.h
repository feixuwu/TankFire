// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Templates/SubclassOf.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKFIRE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

public:

	ATankPlayerController();

	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;
	virtual ASpectatorPawn* SpawnSpectatorPawn() override;
	virtual void GetPlayerViewPoint(FVector& out_Location, FRotator& out_Rotation) const override;
	virtual void GameHasEnded(class AActor* EndGameFocus = NULL, bool bIsWinner = false) override;
	//virtual void PawnPendingDestroy(APawn* inPawn) override;
	virtual void ClientGameEnded_Implementation(class AActor* EndGameFocus, bool bIsWinner);
	virtual void SpawnPlayerCameraManager() override;
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION(BlueprintCallable)
	void ChangeToSpectatorState();

	UFUNCTION(BlueprintImplementableEvent)
	void OnGameEnd();

	UFUNCTION(Reliable, Client)
	void OnNotifyClientKill(const FString& deathName);

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "NotifyClientKill")
	void K2_NotifyClientKill(const FString& deathName);

	UFUNCTION(Reliable, Client)
	void OnNotifyClientBeKilled(const FString& killerName);

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "NotifyClientBeKilled")
	void K2_NotifyClientBeKilled(const FString& killerName);

	void RandomTankColor();


	virtual void Possess(APawn* aPawn) override;
	virtual void UnPossess() override;
	virtual void Tick(float DeltaSeconds) override;

	bool IsGameFinish();

	void ResumeBullet(float DeltaSeconds);
	void ReliveCheck(float DeltaSeconds);
	void processBeKilled(AController* killer);
	void processInvincible(float DeltaSeconds);

	void FindInitCameraViewPoint(FVector& out_Location, FRotator& out_Rotation) const;

	UPROPERTY(EditAnywhere, NoClear, BlueprintReadWrite, Category = Classes)
	TSubclassOf<AActor> InitCameraClass;

	UPROPERTY(EditAnywhere, NoClear, BlueprintReadWrite, Category = Classes)
	float ReliveCountDownTime;

	UPROPERTY(EditAnywhere, NoClear, BlueprintReadWrite, Category = Classes)
	float InvincibleTime;

	FVector DeathCameraLocation;
	FRotator DeathCameraRotator;
	FVector DeathLocation;
	FRotator DeathRotator;

	bool IsDeathCameraSet;
	float ResumeBulletTimeSum;
	
	float ReliveCalcTime;
	bool bNeedRelive;

	float InvincibleCalcTime;
	bool isGameFinish;
};
