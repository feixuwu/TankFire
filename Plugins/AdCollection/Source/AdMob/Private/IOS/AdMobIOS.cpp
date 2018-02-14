#include "AdMob.h"
#include "IOSAppDelegate.h"
#import <AdsUtil/AdsUtil.h>

void FAdMobModule::ShowBanner(enAdsBannerPos pos)
{
    UIViewController* curViewController = (UIViewController*)[IOSAppDelegate GetDelegate].IOSController;

    dispatch_async(dispatch_get_main_queue(), ^{
        [[AdMobHelper GetDelegate] ShowBanner:curViewController isBottom:pos==enAdsBannerPos::enAdsBannerPos_Bottom];
    });
}

void FAdMobModule::HideBanner()
{
    dispatch_async(dispatch_get_main_queue(), ^{
        [[AdMobHelper GetDelegate] HideBanner];
    });
}

void FAdMobModule::ShowInterstitialAd()
{
    UIViewController* curViewController = (UIViewController*)[IOSAppDelegate GetDelegate].IOSController;
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [[AdMobHelper GetDelegate] ShowInterstitialAds:curViewController];
    });
}

void FAdMobModule::PlayRewardedVideo()
{
    UIViewController* curViewController = (UIViewController*)[IOSAppDelegate GetDelegate].IOSController;
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [[AdMobHelper GetDelegate] Play:curViewController];
    });
}

bool FAdMobModule::IsBannerReady()
{
    NSMutableDictionary *resultDictionary = [NSMutableDictionary dictionaryWithCapacity:1];
    [[AdMobHelper GetDelegate] performSelectorOnMainThread:@selector(IsBannerReady:) withObject:resultDictionary waitUntilDone:YES];
    
    NSNumber* number = (NSNumber*)[resultDictionary objectForKey:@"RetValue"];
    bool ret = (bool)[number boolValue];
    
    return ret;
}

bool FAdMobModule::IsInterstitalReady()
{
    NSMutableDictionary *resultDictionary = [NSMutableDictionary dictionaryWithCapacity:1];
    [[AdMobHelper GetDelegate] performSelectorOnMainThread:@selector(IsInterstitalReady:) withObject:resultDictionary waitUntilDone:YES];
    
    NSNumber* number = (NSNumber*)[resultDictionary objectForKey:@"RetValue"];
    bool ret = (bool)[number boolValue];
    
    return ret;
}

bool FAdMobModule::IsRewardedVideoReady()
{
    NSMutableDictionary *resultDictionary = [NSMutableDictionary dictionaryWithCapacity:1];
    [[AdMobHelper GetDelegate] performSelectorOnMainThread:@selector(IsPlayable:) withObject:resultDictionary waitUntilDone:YES];
    
    NSNumber* number = (NSNumber*)[resultDictionary objectForKey:@"RetValue"];
    bool ret = (bool)[number boolValue];
    
    return ret;
}

static void IOS_AdMobPlayComplete(NSString* type, int amount)
{
    FAdMobModule* pModule = FModuleManager::Get().LoadModulePtr<FAdMobModule>(TEXT("AdMob") );
    if (pModule == nullptr) return;
    
    
    FRewardedStatus status;
    status.AdType = EAdType::AdMob;
    
    status.AdMobItem.Type = UTF8_TO_TCHAR([type cStringUsingEncoding:NSUTF8StringEncoding]);
    status.AdMobItem.Amount = (int)amount;
    
    pModule->TriggerPlayRewardCompleteDelegates(status);
}

void FAdMobModule::StartupModule()
{
    bool isEnable = false;
    
    GConfig->GetBool(TEXT("/Script/AdCollectionEditor.AdMobSetting"), TEXT("bIOSEnabled"), isEnable, GEngineIni);
    if(isEnable)
    {
        FString appId;
        GConfig->GetString(TEXT("/Script/AdCollectionEditor.AdMobSetting"), TEXT("IOSAppId"), appId, GEngineIni);
        
        FString bannerUnit;
        GConfig->GetString(TEXT("/Script/AdCollectionEditor.AdMobSetting"), TEXT("IOSBannerUnit"), bannerUnit, GEngineIni);
        
        FString InterstitalUnit;
        GConfig->GetString(TEXT("/Script/AdCollectionEditor.AdMobSetting"), TEXT("IOSInterstitialUnit"), InterstitalUnit, GEngineIni);
        
        FString rewardedUnit;
        GConfig->GetString(TEXT("/Script/AdCollectionEditor.AdMobSetting"), TEXT("IOSRewardedVideoAdUnit"), rewardedUnit, GEngineIni);
        
        
        UIViewController* curViewController = (UIViewController*)[IOSAppDelegate GetDelegate].IOSController;
        
        dispatch_async(dispatch_get_main_queue(), ^{
            [[AdMobHelper GetDelegate] InitSDK:curViewController AppID:[NSString stringWithFString:appId] BannerUnit:[NSString stringWithFString:bannerUnit]  InterstitalUnit:[NSString stringWithFString:InterstitalUnit] RewardedUnit:[NSString stringWithFString:rewardedUnit] callback:&IOS_AdMobPlayComplete];
        });
    }
}

void FAdMobModule::ShutdownModule()
{
    // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
    // we call this function before unloading the module.
    
}
