// Fill out your copyright notice in the Description page of Project Settings.

#include "AdCollection.h"
#include "PlayRewardVideoCallbackProxy.h"


UPlayRewardVideoCallbackProxy::UPlayRewardVideoCallbackProxy() :
	Delegate(FPlayRewardCompleteDelegate::CreateUObject(this, &ThisClass::OnComplete))
{
}


UPlayRewardVideoCallbackProxy* UPlayRewardVideoCallbackProxy::PlayRewardedVideo(EAdType AdType)
{
	IAdModuleInterface* Module = FindAdsModule(AdType);
	if (Module != NULL)
	{
		UPlayRewardVideoCallbackProxy* Proxy = NewObject<UPlayRewardVideoCallbackProxy>();
		Proxy->AdType = AdType;

		return Proxy;
	}

	return nullptr;
}

IAdModuleInterface* UPlayRewardVideoCallbackProxy::FindAdsModule(EAdType adType)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EAdType"), true);
	if (!EnumPtr) return nullptr;

	FString EnumName = EnumPtr->GetNameByValue((int64)adType).ToString();

	FName adPlatformName;
	int32 ScopeIndex = EnumName.Find(TEXT("::"), ESearchCase::CaseSensitive);
	if (ScopeIndex != INDEX_NONE)
	{
		adPlatformName = FName(*EnumName.Mid(ScopeIndex + 2));
	}
	else
	{
		adPlatformName = FName(*EnumName);
	}

	IAdModuleInterface * Module = FModuleManager::Get().LoadModulePtr<IAdModuleInterface>(adPlatformName);

	return Module;
}


void UPlayRewardVideoCallbackProxy::OnComplete(FRewardedStatus Status)
{
	IAdModuleInterface* Module = FindAdsModule(AdType);
	if (Module == nullptr)
	{
		return;
	}

	OnSuccess.Broadcast(Status);

	Module->ClearPlayRewardCompleteDelegate_Handle(DelegateHandle);
}

void UPlayRewardVideoCallbackProxy::Activate()
{
	IAdModuleInterface* Module = FindAdsModule(AdType);
	if (Module != NULL)
	{
		Module->ClearAllPlayRewardCompleteDelegate_Handle();
		DelegateHandle = Module->AddPlayRewardCompleteDelegate_Handle(Delegate);
		Module->PlayRewardedVideo();
	}
}
