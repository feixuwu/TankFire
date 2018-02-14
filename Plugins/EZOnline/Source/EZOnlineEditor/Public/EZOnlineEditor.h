
#pragma once

#include "ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FEZOnlineEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

};