#include "EZOnlineEditor.h"

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "PropertyEditorModule.h"
#include "ServerConfig.h"
#include "ISettingsModule.h"

#include "LevelEditor.h"


#define LOCTEXT_NAMESPACE "FEZOnlineEditorModule"

void FEZOnlineEditorModule::StartupModule()
{
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		
		SettingsModule->RegisterSettings(TEXT("Project"), TEXT("EZOnline"), TEXT("ServerConfig"),
			LOCTEXT("ServerConfig", "Settings"),
			LOCTEXT("ServerConfig", "Settings"),
			GetMutableDefault<UServerConfig>()
		);

		
	}
}

void FEZOnlineEditorModule::ShutdownModule()
{
}



#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEZOnlineEditorModule, EZOnlineEditor)
