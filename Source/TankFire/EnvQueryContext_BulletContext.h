// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_BlueprintBase.h"
#include "Templates/SubclassOf.h"
#include "EnvQueryContext_BulletContext.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TANKFIRE_API UEnvQueryContext_BulletContext : public UEnvQueryContext
{
	GENERATED_BODY()

public:

	UEnvQueryContext_BulletContext();

	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
	

public:

	UPROPERTY(EditAnywhere, Category = Context)
	TSubclassOf<AActor> SearchedActorClass;

	UPROPERTY(EditAnywhere, Category = Context)
	float CheckDistance;

	UPROPERTY(EditAnywhere, Category = Context)
	float Radius;
};
