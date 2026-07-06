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
		if (Button->TuiHasUserFocus())
		{
			return true;
		}
	}

	return false;
}

void UThematicUIDropDownMenuSelection::HandleTickCheckForUserFocus()
{
	if (CheckUserFocus())
	{
		return;
	}
	else
	{
		OnTuiOnOptionSelected.Broadcast(-1);
	}
}

void UThematicUIDropDownMenuSelection::CreateOptionButtons()
{
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
		
		if (i == 0)
		{
			Button->SetUserFocus(GetOwningPlayer());
		}
	}
}

void UThematicUIDropDownMenuSelection::SetupButtonNavigation()
{
	TArray<TObjectPtr<UThematicUIButton>> Buttons;
	SelectionButtonsMap.GetKeys(Buttons);
	
	for (int i = 0; i < Buttons.Num(); i++)
	{
		Buttons[i]->SetAllNavigationRules(EUINavigationRule::Stop, NAME_None);
		
		if (i == 0)
		{
			Buttons[i]->SetNavigationRuleBase(EUINavigation::Up, EUINavigationRule::Escape);
		}
		else if (i == Buttons.Num() - 1)
		{
			Buttons[i]->SetNavigationRuleBase(EUINavigation::Down, EUINavigationRule::Escape);
		}
		
		if (Buttons.IsValidIndex(i - 1))
		{
			Buttons[i]->SetNavigationRuleExplicit(EUINavigation::Up, Buttons[i - 1]);
		}
		if (Buttons.IsValidIndex(i + 1))
		{
			Buttons[i]->SetNavigationRuleExplicit(EUINavigation::Down, Buttons[i + 1]);
		}
	}
}

void UThematicUIDropDownMenuSelection::HandleOptionSelected(UThematicUIButton* ButtonPressed)
{
	
}

void UThematicUIDropDownMenuSelection::NativeCreated(UThematicUIDropDownMenu* OwnerMenu, TArray<FText>& OptionsArray)
{
	OwningDropDownMenuRef = OwnerMenu;
	
	Options = OptionsArray;
	
	CreateOptionButtons();
	SetupButtonNavigation();
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
