// Fill out your copyright notice in the Description page of Project Settings.

#include "EnvQueryContext_BulletContext.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"


UEnvQueryContext_BulletContext::UEnvQueryContext_BulletContext()
{
	CheckDistance = 1500;
	Radius = 45.0f;
}

void UEnvQueryContext_BulletContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	if (SearchedActorClass == nullptr)
	{
		return;
	}

	TArray<AActor*> findList;
	TArray<FVector> outList;
	UGameplayStatics::GetAllActorsOfClass(this, SearchedActorClass, findList);
	AActor* QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());

	for (int i = 0; i < findList.Num(); i++)
	{
		FVector from = findList[i]->GetActorLocation();
		FVector to = findList[i]->GetActorLocation() + findList[i]->GetActorRotation().RotateVector(FVector(CheckDistance, 0, 0) );

		FHitResult hitResult;
		if (UKismetSystemLibrary::SphereTraceSingle(QueryOwner, from, to, Radius, UEngineTypes::ConvertToTraceType(ECC_Camera), false, TArray<AActor*>(), EDrawDebugTrace::None, hitResult, false))
		{
			if (hitResult.Actor == QueryOwner)
			{
				outList.Add(findList[i]->GetActorLocation() );
			}
		}
	}

	if (outList.Num() == 0)
	{
		outList.Add(FVector(-10000, 10000, 10000) );
	}
	UEnvQueryItemType_Point::SetContextHelper(ContextData, outList);
}
