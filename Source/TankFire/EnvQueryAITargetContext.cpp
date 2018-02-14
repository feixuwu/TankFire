// Fill out your copyright notice in the Description page of Project Settings.

#include "EnvQueryAITargetContext.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "TankPlayerState.h"

void UEnvQueryAITargetContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	if (TargetClass == nullptr)
	{
		return;
	}

	UObject* QueryOwner = QueryInstance.Owner.Get();
	if (QueryOwner == nullptr)
	{
		return;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(QueryOwner, EGetWorldErrorMode::LogAndReturnNull);
	if (World == nullptr)
	{
		return;
	}

	AActor* QuerierActor = Cast<AActor>(QueryOwner);
	TArray<AActor*> ActorSet;
	for (TActorIterator<AActor> ItActor = TActorIterator<AActor>(World, TargetClass); ItActor; ++ItActor)
	{
		if (QuerierActor == *ItActor)
		{
			continue;
		}

		ATankCharacter* pTankCharacter = Cast<ATankCharacter>(*ItActor);
		if (pTankCharacter == nullptr || pTankCharacter->IsPendingKill() )
		{
			continue;
		}

		ATankPlayerState* pTankPlayerState = Cast<ATankPlayerState>(pTankCharacter->PlayerState);
		if (pTankPlayerState == nullptr || pTankPlayerState->IsPendingKill() || pTankPlayerState->isInvincible)
		{
			continue;
		}

		ActorSet.Add(*ItActor);
	}

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, ActorSet);
}
