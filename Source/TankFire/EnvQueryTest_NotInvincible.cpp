// Fill out your copyright notice in the Description page of Project Settings.

#include "EnvQueryTest_NotInvincible.h"
#include "TankCharacter.h"
#include "TankPlayerState.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"

UEnvQueryTest_NotInvincible::UEnvQueryTest_NotInvincible()
{
	Cost = EEnvTestCost::Low;

	// "Random" is completely agnostic on item type!  Any type at all is valid!
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
}

void UEnvQueryTest_NotInvincible::RunTest(FEnvQueryInstance& QueryInstance) const
{
	UObject* QueryOwner = QueryInstance.Owner.Get();
	if (QueryOwner == nullptr)
	{
		return;
	}

	FloatValueMin.BindData(QueryOwner, QueryInstance.QueryID);
	float MinThresholdValue = FloatValueMin.GetValue();

	FloatValueMax.BindData(QueryOwner, QueryInstance.QueryID);
	float MaxThresholdValue = FloatValueMax.GetValue();

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());
		ATankCharacter* pItemCharacter = Cast<ATankCharacter>(ItemActor);
		if (pItemCharacter != nullptr)
		{
			ATankPlayerState* pTankPlayerState = Cast<ATankPlayerState>(pItemCharacter->PlayerState);
			if (pTankPlayerState != nullptr)
			{
				It.SetScore(EEnvTestPurpose::Type::Filter, EEnvTestFilterType::Type::Match, pTankPlayerState->isInvincible == false, true);
			}
		}
	}
}

FText UEnvQueryTest_NotInvincible::GetDescriptionDetails() const
{
	return DescribeFloatTestParams();
}