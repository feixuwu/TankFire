// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "AdCollectionBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EAdType : uint8
{
	AdMob 	UMETA(DisplayName = "AdMob")
};


/*UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ERewardState : uint8
{
	COMPLETED 	UMETA(DisplayName = "COMPLETED"),
	CLICKED 	UMETA(DisplayName = "CLICKED")
};*/


USTRUCT(BlueprintType)
struct FAdMobRewardItem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Amount;
};


USTRUCT(BlueprintType)
struct FRewardedStatus
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EAdType AdType;

		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FAdMobRewardItem  AdMobItem;

		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 ChartBoostReward;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayRewardedDelegate, FRewardedStatus, RewardStatus);

UCLASS()
class UAdCollectionBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SimplePlayRewardedVideo", Keywords = "AdCollection Play"), Category = "AdCollection")
	static void PlayAdVideo(EAdType adType);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ShowBanner", Keywords = "AdCollection Show Banner"), Category = "AdCollection")
	static void ShowBanner(EAdType adType, bool isOnBottom);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "HideBanner", Keywords = "AdCollection Hide Banner"), Category = "AdCollection")
	static void HideBanner(EAdType adType);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ShowInterstitial", Keywords = "AdCollection Show Interstitial Ads"), Category = "AdCollection")
	static void ShowInterstitial(EAdType adType);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "IsBannerAdsReady", Keywords = "AdCollection Check Banner Ads Ready"), Category = "AdCollection")
	static bool IsBannerReady(EAdType adType);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "IsInterstitialAdsReady", Keywords = "AdCollection Check Interstital Ads Ready"), Category = "AdCollection")
	static bool IsInterstitialReady(EAdType adType);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "IsRewardedVideoAdsReady", Keywords = "AdCollection Check RewardedVideo Ads Ready"), Category = "AdCollection")
	static bool IsRewardedVideoReady(EAdType adType);
};
