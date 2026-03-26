// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicData/ThematicUIThemeData.h"

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
	if (ParentThematicUIThemeDataAsset)
	{
		ThematicUIThemeData = ThematicUIThemeDataOverride.ConvertToThemeData(ThematicUIThemeData);
	}
	
	return ThematicUIThemeData;
}

void UThematicUIThemeDataAsset::SetThematicUIThemeData(const FThematicUIThemeData& NewThematicUIThemeData)
{
	ThematicUIThemeData = NewThematicUIThemeData;
}
