// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AdCollectionBPLibrary.h"
#include "AdCollection.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "PlayRewardVideoCallbackProxy.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class  UPlayRewardVideoCallbackProxy : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPlayRewardVideoCallbackProxy();
	UPROPERTY(BlueprintAssignable)
	FPlayRewardedDelegate OnSuccess;


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PlayRewardedVideo", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "AdCollection")
	static UPlayRewardVideoCallbackProxy* PlayRewardedVideo(EAdType AdType);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;

	static IAdModuleInterface* FindAdsModule(EAdType adType);

	EAdType AdType;
	
private:

	FPlayRewardCompleteDelegate Delegate;
	FDelegateHandle DelegateHandle;

	void OnComplete(FRewardedStatus Status);
};
