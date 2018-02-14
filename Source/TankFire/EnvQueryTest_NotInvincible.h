// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_NotInvincible.generated.h"

/**
 * 
 */
UCLASS()
class TANKFIRE_API UEnvQueryTest_NotInvincible : public UEnvQueryTest
{
	GENERATED_BODY()

public:

	UEnvQueryTest_NotInvincible();
	
protected:
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;

	virtual FText GetDescriptionDetails() const override;
	
	
};
