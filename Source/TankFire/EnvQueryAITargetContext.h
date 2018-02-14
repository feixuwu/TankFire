// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/Actor.h"
#include "TankCharacter.h"
#include "EnvQueryAITargetContext.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TANKFIRE_API UEnvQueryAITargetContext : public UEnvQueryContext
{
	GENERATED_BODY()
	
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
	

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATankCharacter> TargetClass;
};
