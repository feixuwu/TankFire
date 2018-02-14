#include "AdMob.h"


void FAdMobModule::ShowBanner(enAdsBannerPos pos)
{
}

void FAdMobModule::HideBanner()
{

}

void FAdMobModule::ShowInterstitialAd()
{

}

void FAdMobModule::PlayRewardedVideo()
{
}

bool FAdMobModule::IsBannerReady()
{
	return false;
}

bool FAdMobModule::IsInterstitalReady()
{
	return false;
}

bool FAdMobModule::IsRewardedVideoReady()
{
	return false;
}

void FAdMobModule::StartupModule()
{
    // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    
}

void FAdMobModule::ShutdownModule()
{
    // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
    // we call this function before unloading the module.
    
}
