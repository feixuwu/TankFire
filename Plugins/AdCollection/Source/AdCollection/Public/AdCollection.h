// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ModuleManager.h"
#include "AdCollectionBPLibrary.h"

class FAdCollectionModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

enum enAdsBannerPos
{
	enAdsBannerPos_Top = 0,
	enAdsBannerPos_Bottom,
};


DECLARE_MULTICAST_DELEGATE_OneParam(FPlayRewardComplete, FRewardedStatus);
typedef FPlayRewardComplete::FDelegate FPlayRewardCompleteDelegate;

#define DEFINE_ADS_DELEGATE_BASE(DelegateName) \
public: \
	F##DelegateName DelegateName##Delegates; \
public: \
	virtual FDelegateHandle Add##DelegateName##Delegate_Handle(const F##DelegateName##Delegate& Delegate) \
	{ \
		DelegateName##Delegates.Add(Delegate); \
		return Delegate.GetHandle(); \
	} \
	virtual void Clear##DelegateName##Delegate_Handle(FDelegateHandle& Handle) \
	{ \
		DelegateName##Delegates.Remove(Handle); \
		Handle.Reset(); \
	}\
	virtual void ClearAll##DelegateName##Delegate_Handle() \
	{ \
		DelegateName##Delegates.Clear(); \
	}


#define DEFINE_ADS_DELEGATE_ONE_PARAM(DelegateName, Param1Type) \
	DEFINE_ADS_DELEGATE_BASE(DelegateName) \
	virtual void Trigger##DelegateName##Delegates(Param1Type Param1) \
	{ \
		DelegateName##Delegates.Broadcast(Param1); \
	}

class IAdModuleInterface :public IModuleInterface
{
public:

	virtual void ShowBanner(enAdsBannerPos pos)
	{
	}

	virtual void HideBanner()
	{
	}

	virtual void PlayRewardedVideo() 
	{
	}

	virtual void ShowInterstitialAd()
	{

	}

	virtual bool IsBannerReady()
	{
		return false;
	}

	virtual bool IsInterstitalReady()
	{
		return false;
	}

	virtual bool IsRewardedVideoReady()
	{
		return false;
	}

	DEFINE_ADS_DELEGATE_ONE_PARAM(PlayRewardComplete, FRewardedStatus);
};