// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AdCollectionEditor.h"

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "PropertyEditorModule.h"
#include "AdMobSetting.h"
#include "ISettingsModule.h"

#include "LevelEditor.h"

static const FName AdCollectionEditorTabName("AdCollectionEditor");

#define LOCTEXT_NAMESPACE "FAdCollectionEditorModule"

void FAdCollectionEditorModule::StartupModule()
{
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		SettingsModule->RegisterSettings(TEXT("Project"), TEXT("AdCollection"), TEXT("AdMob"),
			LOCTEXT("AdMob", "AdMob"),
			LOCTEXT("AdMob", "Settings for AdMob"),
			GetMutableDefault<UAdMobSetting>()
		);
		
	}
}

void FAdCollectionEditorModule::ShutdownModule()
{
}



#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAdCollectionEditorModule, AdCollectionEditor)
