// Fill out your copyright notice in the Description page of Project Settings.

#include "ThematicData/ThematicUIThemeData.h"
#include "ThematicUI.h"

#if WITH_EDITOR
void UThematicUIThemeDataAsset::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = PropertyChangedEvent.GetPropertyName();
	
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UThematicUIThemeDataAsset, ParentThematicUIThemeDataAsset))
	{
		if (ParentThematicUIThemeDataAsset)
		{
			ThematicUIThemeDataOverride = ThematicUIThemeDataOverride.ConvertFromThemeData(ParentThematicUIThemeDataAsset->GetThematicUIThemeData());
		}
		else
		{
			ThematicUIThemeDataOverride = FThematicUIThemeDataOverride();
		}
	}
	
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

const FThematicUIThemeData& UThematicUIThemeDataAsset::GetThematicUIThemeData()
{
	if (ParentThematicUIThemeDataAsset == this)
	{
		UE_LOGFMT(LogThematicUI, Error, "CANNOT BE IT'S OWN PARENT");
		return ThematicUIThemeData;
	}
	
	if (ParentThematicUIThemeDataAsset)
	{
		// @todo Update To New API
		ThematicUIThemeData = ThematicUIThemeDataOverride.ConvertToThemeData(ParentThematicUIThemeDataAsset->GetThematicUIThemeData());
	}
	
	return ThematicUIThemeData;
}

void UThematicUIThemeDataAsset::SetThematicUIThemeData(const FThematicUIThemeData& NewThematicUIThemeData)
{
	ThematicUIThemeData = NewThematicUIThemeData;
}

const FThematicUIThemeDataOverride UThematicUIThemeDataAsset::GetThematicUIThemeDataOverride()
{
	if (ParentThematicUIThemeDataAsset == this)
	{
		// @todo Update To New API
		UE_LOGFMT(LogThematicUI, Error, "CANNOT BE IT'S OWN PARENT");
		return ThematicUIThemeDataOverride.ForceToThemeOverrideData(ThematicUIThemeData);
	}
	
	if (ParentThematicUIThemeDataAsset)
	{
		return ThematicUIThemeDataOverride;
	}
	
	// @todo Update To New API
	return ThematicUIThemeDataOverride.ForceToThemeOverrideData(ThematicUIThemeData);
}
