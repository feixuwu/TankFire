// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBullet.h"
#include "Delegates/Delegate.h"
#include "TankCharacter.h"
#include "Engine/CollisionProfile.h"

// Sets default values
ATankBullet::ATankBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComponent->SetSphereRadius(45.0f);

	SphereComponent->BodyInstance.SetCollisionProfileName("Projectile");
	RootComponent = SphereComponent;

	SphereComponent->OnComponentHit.AddDynamic(this, &ATankBullet::OnBulletHit);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATankBullet::OnBulletBeginOverlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh") );
	Mesh->SetupAttachment(SphereComponent);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow") );
	Arrow->SetupAttachment(SphereComponent);

	ProjectTitle = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectTitle");
	ProjectTitle->SetUpdatedComponent(GetRootComponent());
	ProjectTitle->InitialSpeed = 1200;
	ProjectTitle->bRotationFollowsVelocity = true;
	ProjectTitle->bShouldBounce = true;
	ProjectTitle->Bounciness = 1.0f;
	
	bReplicateMovement = false;
	
	// set max alive time
	InitialLifeSpan = 25.0f;
}

void ATankBullet::OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// only run on server
	if (!HasAuthority())
	{
		return;
	}

	HitCount++;

	if (HitCount > 1 && !IsPendingKill() )
	{
		Destroy();
	}
}

void ATankBullet::OnBulletBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// only run on server
	if (!HasAuthority())
	{
		return;
	}

	ATankBullet* otherBullet = Cast<ATankBullet>(OtherActor);
	if (otherBullet != nullptr)
	{
		if ( (GetOwner() == otherBullet->GetOwner() ) && HitCount == 0 && otherBullet->HitCount == 0)
		{
			return;
		}

		if (!IsPendingKill())
		{
			Destroy();
		}

		if (!otherBullet->IsPendingKill())
		{
			otherBullet->Destroy();
		}
		return;
	}

	ATankCharacter* otherTankCharacter = Cast<ATankCharacter>(OtherActor);
	if (otherTankCharacter == nullptr)
	{
		return;
	}

	otherTankCharacter->OnDeath(Cast<AController>(GetOwner()), this);
	Destroy();
}

// Called when the game starts or when spawned
void ATankBullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

