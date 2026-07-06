// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/ThematicUIDropDownMenuSelection.h"

#include "Components/ScrollBox.h"
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
		//OnTuiOnOptionSelected.Broadcast(-1);
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

void UThematicUIDropDownMenuSelection::NativeCreated(UThematicUIDropDownMenu* OwnerMenu, TArray<FText>& OptionsArray)
{
	OwningDropDownMenuRef = OwnerMenu;
	
	Options = OptionsArray;
	
	if (!DropDownButtonSubclass->IsValidLowLevel())
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUIDropDownMenuSelection::NativeCreated, {Name}::DropDownButtonSubclass is NOT VALID", GetName());
		return;
	}
	
	for (int i = 0; i < Options.Num(); i++)
	{
		UThematicUIButton* Button = CreateWidget<UThematicUIButton>(this, DropDownButtonSubclass, NAME_None);
		
		verifyf(Button != nullptr, TEXT("UThematicUIDropDownMenuSelection::NativeCreated, Button Created For Options Menu == nullptr"));
		
		ScrollBox->AddChild(Button);
		Button->SetPrimaryWidgetData(PrimaryWidgetData);
		
		SelectionButtonsMap.Add(Button, i);
	}
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
