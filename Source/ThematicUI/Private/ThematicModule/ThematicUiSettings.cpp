// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicModule/ThematicUiSettings.h"

#include "InputMappingContext.h"
#include "InputAction.h"

UInputMappingContext* UThematicUiSettings::GetDefaultInputMappingContext() const
{
	ensureMsgf(bInputDataLoaded, TEXT("Warning, Thematic Ui Input data not loaded."));
	
	return DefaultCommonInputMappingContextClass;
}

UInputAction* UThematicUiSettings::GetDefaultClickInputAction() const
{
	ensureMsgf(bInputDataLoaded, TEXT("Warning, Thematic Ui Input data not loaded."));
	
	return DefaultClickInputActionClass;
}

void UThematicUiSettings::LoadData()
{
	LoadInputData();
}

void UThematicUiSettings::LoadInputData()
{
	if (!bInputDataLoaded)
	{
		// If we were created early enough to be disregarded by the GC (which we should be), then we need to 
		// add all of our members to the root set, since our hard reference to them is totally meaningless to the GC.
		const bool bIsDisregardForGC = GUObjectArray.IsDisregardForGC(this);
		
		DefaultCommonInputMappingContextClass = DefaultInputMappingContext.LoadSynchronous();
		if (DefaultClickInputActionClass)
		{
			if (bIsDisregardForGC)
			{
				DefaultCommonInputMappingContextClass->AddToRoot();
			}
		}
		
		DefaultClickInputActionClass = DefaultClickInputAction.LoadSynchronous();
		if (DefaultClickInputActionClass)
		{
			if (bIsDisregardForGC)
			{
				DefaultClickInputActionClass->AddToRoot();
			}
		}
	}
	
}
