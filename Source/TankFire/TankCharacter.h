// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TankBullet.h"
#include "TankCharacter.generated.h"


class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TANKFIRE_API ATankCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATankCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnRep_PlayerState() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnRepPlayerState();

	void HandleMoveForward(float axis);
	void HandleMoveRight(float axis);
	void HandFire();
	
	UFUNCTION(BlueprintNativeEvent)
	void OnDeath(AController* killer, AActor* pBullet);

	UFUNCTION(BlueprintImplementableEvent)
	void OnHitWithVelocity(FVector velocity);

	UFUNCTION(Server, Reliable, WithValidation)
	void Shoot(const FRotator& rotation);

	UFUNCTION(BlueprintCallable, DisplayName="Shoot")
	void BP_Shoot(const FRotator& rotation);

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* TankBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* CameraArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* GunArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* GunRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* TankGun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATankBullet> BulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> KnockoutClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float KnckoutSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float KnockNormalZ;

	FVector HitSpeed;
};
