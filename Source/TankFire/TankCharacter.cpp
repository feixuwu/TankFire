// Fill out your copyright notice in the Description page of Project Settings.

#include "TankCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TankPlayerController.h"
#include "TankAIController.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TankPlayerState.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/GameMode.h"

// Sets default values
ATankCharacter::ATankCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	TankBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankBody") );
	if (TankBody != nullptr)
	{
		TankBody->SetupAttachment(GetRootComponent() );
	}

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	if (CameraArm != nullptr)
	{
		CameraArm->SetupAttachment(GetRootComponent());
		CameraArm->bUsePawnControlRotation = false;
		CameraArm->bInheritYaw = false;
		CameraArm->bInheritRoll = false;
		CameraArm->bInheritPitch = false;


		Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
		Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	}

	GunArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("GunArm"));
	if (GunArm != nullptr)
	{
		GunArm->SetupAttachment(GetRootComponent());
		GunArm->bUsePawnControlRotation = false;
		GunArm->bInheritYaw = false;
		GunArm->bInheritRoll = false;
		GunArm->bInheritPitch = false;

		GunRoot = CreateDefaultSubobject<USceneComponent>(TEXT("GunRoot"));
		GunRoot->SetupAttachment(GunArm, USpringArmComponent::SocketName);

		TankGun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankGun"));
		TankGun->SetupAttachment(GunRoot);
	}

	UCharacterMovementComponent* pCharacterMovement = GetCharacterMovement();
	if (pCharacterMovement != nullptr)
	{
		pCharacterMovement->bOrientRotationToMovement = true;
	}

	KnckoutSpeed = 2000;
	KnockNormalZ = 0.8f;
}

// Called when the game starts or when spawned
void ATankCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATankCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATankCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATankCharacter::HandleMoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ATankCharacter::HandleMoveRight);

	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ATankCharacter::HandFire);
}

void ATankCharacter::HandleMoveForward(float axis)
{
	float value = FMath::Sign(axis);
	FRotator controllRotation = GetControlRotation();

	FVector forwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0, controllRotation.Yaw, 0) );

	AddMovementInput(forwardVector, value);
}

void ATankCharacter::HandleMoveRight(float axis)
{
	float value = FMath::Sign(axis);
	FRotator controllRotation = GetControlRotation();

	FVector forwardVector = UKismetMathLibrary::GetRightVector(FRotator(0, controllRotation.Yaw, 0));

	AddMovementInput(forwardVector, value);
}

void ATankCharacter::HandFire()
{
	ATankPlayerController* PlayerController = Cast<ATankPlayerController>(GetController() );
	if (PlayerController == nullptr)
	{
		return;
	}

	float xPos = 0;
	float yPos = 0;
	if (!PlayerController->GetMousePosition(xPos, yPos) )
	{
		bool isCurPressed = false;
		PlayerController->GetInputTouchState(ETouchIndex::Touch1, xPos, yPos, isCurPressed);
		if (!isCurPressed)
		{
			PlayerController->GetInputTouchState(ETouchIndex::Touch2, xPos, yPos, isCurPressed);
		}

		if (!isCurPressed)
		{
			return;
		}
	}

	FVector worldPos;
	FVector worldDirection;
	if (!PlayerController->DeprojectScreenPositionToWorld(xPos, yPos, worldPos, worldDirection))
	{
		return;
	}

	worldDirection = worldDirection.GetSafeNormal();

	FVector location = GetActorLocation();
	FVector hitPos = worldPos + worldDirection * ((location.Z - worldPos.Z) / worldDirection.Z);

	FVector shootDir = (hitPos - location).GetSafeNormal();
	FRotator shootRot = UKismetMathLibrary::MakeRotFromX(shootDir);

	// local shoot
	GunRoot->SetWorldRotation(shootRot);
	ATankPlayerState* pState = Cast<ATankPlayerState>(PlayerController->PlayerState);
	if (pState == nullptr || pState->CurBulletCount <= 0)
	{
		return;
	}

	// shoot on server
	Shoot(shootRot);
}

bool ATankCharacter::Shoot_Validate(const FRotator& rotation)
{
	AGameMode* GameMode = Cast<AGameMode>(UGameplayStatics::GetGameMode(this) );
	if (GameMode != nullptr && GameMode->HasMatchEnded() == false)
	{
		return true;
	}

	return false;
}

void ATankCharacter::BP_Shoot(const FRotator& rotation)
{
	Shoot(rotation);
}

void ATankCharacter::OnRep_PlayerState()
{
	OnRepPlayerState();
}

void ATankCharacter::Shoot_Implementation(const FRotator& rotation)
{

	if (BulletClass == nullptr)
	{
		return;
	}

	if (GetController() == nullptr)
	{
		return;
	}

	ATankPlayerState* pState = Cast<ATankPlayerState>(GetController()->PlayerState);
	if (pState == nullptr || pState->CurBulletCount <= 0)
	{
		return;
	}
	pState->CurBulletCount--;

	FActorSpawnParameters params;
	params.Owner = GetController();
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
	FVector location = GetActorLocation() + rotation.RotateVector(FVector(200.0f, 0, -130.0f) );
	UClass* pBulletClass = BulletClass;
	GetWorld()->SpawnActor<ATankBullet>(pBulletClass, location, rotation, params);
}

void ATankCharacter::OnDeath_Implementation(AController* killer, AActor* pBullet)
{
	ATankPlayerController* pSelfControler = Cast<ATankPlayerController>(GetController() );
	if (pSelfControler != nullptr)
	{
		ATankPlayerState* pSelfState = Cast<ATankPlayerState>(GetController()->PlayerState);
		if (pSelfState && pSelfState->isInvincible == false)
		{
			pSelfControler->processBeKilled(killer);
		}
		else
		{
			return;
		}
	}

	ATankAIController* pAIController = Cast<ATankAIController>(GetController());
	if (pAIController != nullptr)
	{
		ATankPlayerState* pSelfState = Cast<ATankPlayerState>(GetController()->PlayerState);
		if (pSelfState && pSelfState->isInvincible == false)
		{
			pAIController->processBeKilled(killer);
		}
		else
		{
			return;
		}
	}

	if (KnockoutClass != nullptr && pBullet != nullptr)
	{
		HitSpeed = pBullet->GetVelocity();
		HitSpeed = HitSpeed.GetSafeNormal2D();
		HitSpeed.Z = KnockNormalZ;
		HitSpeed = HitSpeed.GetSafeNormal();

		FActorSpawnParameters params;
		params.Owner = GetController();
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FVector location = GetActorLocation() + HitSpeed * 100;

		OnHitWithVelocity(HitSpeed);
	}

	Destroy();
}
