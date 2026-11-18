// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>
#include <Logging/StructuredLog.h>
#include <Misc/AutomationTest.h>
#include <Modules/ModuleManager.h>

DECLARE_LOG_CATEGORY_EXTERN(LogThematicUI, Log, All)

class FThematicUiModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	
	virtual void ShutdownModule() override;
	
	static inline FThematicUiModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FThematicUiModule>("ThematicUI");
	}
	
	static bool BindMappingContext(const UObject* WorldContextObject);
	
	virtual class UThematicUiSettings* GetThematicUiSettings();
	
protected:
	
	
private:
	void CreateInputSettings();
	
	UThematicUiSettings* ThematicUiSettings = nullptr;
};
