// Fill out your copyright notice in the Description page of Project Settings.

#include "TankFire.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"
#include "Misc/NetworkVersion.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FTankFireModule, TankFire, "TankFire" );

void FTankFireModule::StartupModule()
{
	FNetworkVersion::bHasCachedNetworkChecksum = false;
	FNetworkVersion::GetLocalNetworkVersionOverride.BindLambda([]() {

		FString VersionString = TEXT("TankNetworkVersion1");
		uint32 CheckSum = FCrc::StrCrc32(*VersionString.ToLower());

		return CheckSum;
	});
}

void FTankFireModule::ShutdownModule()
{

}