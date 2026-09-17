// Fill out your copyright notice in the Description page of Project Settings.

#include "ThematicData/ThematicUiThemeData.h"

#include <Misc/DataValidation.h>

#include "ThematicUI.h"

#if WITH_EDITOR
void UThematicUiThemeDataAsset::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = PropertyChangedEvent.GetPropertyName();
	
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UThematicUiThemeDataAsset, ParentThematicUIThemeDataAsset))
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

const FThematicUiThemeData& UThematicUiThemeDataAsset::GetThematicUIThemeData()
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

void UThematicUiThemeDataAsset::SetThematicUIThemeData(const FThematicUiThemeData& NewThematicUIThemeData)
{
	ThematicUIThemeData = NewThematicUIThemeData;
}

const FThematicUIThemeDataOverride UThematicUiThemeDataAsset::GetThematicUIThemeDataOverride()
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

EDataValidationResult UThematicUiThemeDataAsset::IsDataValid(class FDataValidationContext& Context) const
{
	if (ThematicUIThemeData.NormalTheme.TextFont.FontObject == nullptr)
	{
		Context.AddError(FText::FromString(TEXT("ThematicUIThemeData.NormalTheme.TextFont.FontObject == NULL")));
	}
	
	if (ThematicUIThemeDataOverride.NormalThemeOverride.TextFont.FontObject == nullptr && ParentThematicUIThemeDataAsset != nullptr)
	{
		Context.AddError(FText::FromString(TEXT("ThematicUIThemeDataOverride.NormalThemeOverride.TextFont.FontObject == NULL")));
	}

	return Super::IsDataValid(Context);
}
