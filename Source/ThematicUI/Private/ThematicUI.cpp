// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThematicUI.h"

#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <ISettingsModule.h>
#include <ISettingsSection.h>
#include <Kismet/GameplayStatics.h>

#include "ThematicModule/ThematicUiSettings.h"

#define LOCTEXT_NAMESPACE "FThematicUiModule"

DEFINE_LOG_CATEGORY(LogThematicUI);

void FThematicUiModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	CreateInputSettings();
}

void FThematicUiModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
#if WITH_EDITOR

	//Unregister Settings
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	
	if (SettingsModule != nullptr)
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "ThematicUi");
	}

#endif

	if (!GExitPurge) // If GExitPurge Object is already gone
	{
		ThematicUiSettings->RemoveFromRoot();
	}
	ThematicUiSettings = nullptr;
}

bool FThematicUiModule::BindMappingContext(const UObject* WorldContextObject)
{
	bool didAddMappingContext = false;

	for (int32 index = 0; index < UGameplayStatics::GetNumLocalPlayerControllers(WorldContextObject); index++)
	{	
		APlayerController* controller = UGameplayStatics::GetPlayerController(WorldContextObject, index);
		
		if (!controller) { continue; }
		
		if (UEnhancedInputLocalPlayerSubsystem* localPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(controller->GetLocalPlayer()))
		{
			if (UInputMappingContext* mappingContext = Get().GetThematicUiSettings()->GetDefaultInputMappingContext())
			{
				localPlayerSubsystem->AddMappingContext(mappingContext, 0);
				
				didAddMappingContext = true;
			}
		}
	}
	
	return didAddMappingContext;
}

void FThematicUiModule::CreateInputSettings()
{
	ThematicUiSettings = NewObject<UThematicUiSettings>(GetTransientPackage(), UThematicUiSettings::StaticClass());
	check(ThematicUiSettings);
	ThematicUiSettings->AddToRoot();
	
	ThematicUiSettings->LoadData();
	
#if WITH_EDITOR

	// Register Settings
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	
	if (SettingsModule != nullptr)
	{
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "ThematicUi",
			NSLOCTEXT("ThematicUiPlugin", "ThematicUiSettings", "Thematic Ui Settings"),
			NSLOCTEXT("ThematicUiPlugin", "ThematicUiSettingsDescription", "Configure Thematic Ui Defaults and Settings."),
			ThematicUiSettings
		);
	}

#endif
}

class UThematicUiSettings* FThematicUiModule::GetThematicUiSettings()
{
	return ThematicUiSettings;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FThematicUiModule, ThematicUi)