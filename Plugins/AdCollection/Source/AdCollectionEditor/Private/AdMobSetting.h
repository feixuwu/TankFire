// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "AdMobSetting.generated.h"

/**
 * 
 */
UCLASS(transient, config = Engine)
class UAdMobSetting : public UObject
{
	GENERATED_BODY()
	
		UPROPERTY(Config, EditAnywhere, Category = Android, Meta = (DisplayName = "If AdMob Android Enable"))
		bool bAndroidEnabled;

	UPROPERTY(Config, EditAnywhere, Category = Android, Meta = (DisplayName = "Android AppID"))
		FString AndroidAppId;

	UPROPERTY(Config, EditAnywhere, Category = Android, Meta = (DisplayName = "Android Banner AdUnit"))
		FString AndroidBannerUnit;

	UPROPERTY(Config, EditAnywhere, Category = Android, Meta = (DisplayName = "Android Interstitial AdUnit"))
		FString AndroidInterstitialUnit;

	UPROPERTY(Config, EditAnywhere, Category = Android, Meta = (DisplayName = "Android RewardVideo AdUnit"))
	FString AndroidRewardedVideoAdUnit;
    
    
    UPROPERTY(Config, EditAnywhere, Category = IOS, Meta = (DisplayName = "If AdMob IOS Enable"))
    bool bIOSEnabled;
    
    UPROPERTY(Config, EditAnywhere, Category = IOS, Meta = (DisplayName = "IOS AppID"))
    FString IOSAppId;
    
    UPROPERTY(Config, EditAnywhere, Category = IOS, Meta = (DisplayName = "IOS Banner AdUnit"))
    FString IOSBannerUnit;
    
    UPROPERTY(Config, EditAnywhere, Category = IOS, Meta = (DisplayName = "IOS Interstitial AdUnit"))
    FString IOSInterstitialUnit;
    
    UPROPERTY(Config, EditAnywhere, Category = IOS, Meta = (DisplayName = "IOS RewardVideo AdUnit"))
    FString IOSRewardedVideoAdUnit;
	
#if WITH_EDITOR
		// UObject interface
		virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
};
