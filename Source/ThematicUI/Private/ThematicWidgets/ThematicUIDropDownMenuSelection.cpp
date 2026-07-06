// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/ThematicUIDropDownMenuSelection.h"

#include "ThematicWidgets/ThematicUIButton.h"

bool UThematicUIDropDownMenuSelection::CheckUserFocus()
{
	TArray<TObjectPtr<UThematicUIButton>> Buttons;
	
	SelectionButtonsMap.GetKeys(Buttons);
	
	for (UThematicUIButton* Button : Buttons)
	{
		if (!Button->TuiHasUserFocus())
		{
			return false;
		}
	}

	return true;
}

void UThematicUIDropDownMenuSelection::HandleTickCheckForUserFocus()
{
	if (CheckUserFocus())
	{
		return;
	}
	else
	{
		RemoveFromParent();
	}
}

void UThematicUIDropDownMenuSelection::CreateOptionButtons()
{
	
}

void UThematicUIDropDownMenuSelection::SetupButtonNavigation()
{
	
}

void UThematicUIDropDownMenuSelection::HandleOptionSelected(UThematicUIButton* ButtonPressed)
{
	
}

void UThematicUIDropDownMenuSelection::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	HandleTickCheckForUserFocus();
}

void UThematicUIDropDownMenuSelection::NativeDestruct()
{
	Super::NativeDestruct();
}
