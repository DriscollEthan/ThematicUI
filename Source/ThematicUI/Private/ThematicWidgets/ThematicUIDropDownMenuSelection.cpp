// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/ThematicUIDropDownMenuSelection.h"

#include "Components/ScrollBox.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/BackgroundBlur.h"
#include "Components/Image.h"
#include "Components/ScrollBoxSlot.h"

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
		HandleOptionSelected(-1);
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
		Button->SetPrimaryWidgetData(SelectionMenuData.SelectionMenuWidgetThemeData);
		Button->SetText(Options[i]);
		
		SelectionButtonsMap.Add(Button, i);
		
		if (i == 0)
		{
			Button->SetUserFocus(GetOwningPlayer());
		}
		
		if (UScrollBoxSlot* ScrollBoxSlot = UWidgetLayoutLibrary::SlotAsScrollBoxSlot(Button))
		{
			ScrollBoxSlot->SetPadding(SelectionMenuData.SelectionMenuOptionsPadding);
		}
		
		Button->OnTuiButtonPressedAndReleased.AddUniqueDynamic(this, &ThisClass::HandleOptionSelected);
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
	if (SelectionButtonsMap.Find(ButtonPressed))
	{
		HandleOptionSelected(SelectionButtonsMap.FindRef(ButtonPressed));
	}
}

void UThematicUIDropDownMenuSelection::HandleOptionSelected(int32 SelectedIndex)
{
	OnTuiOnOptionSelected.Broadcast(SelectedIndex);

	TArray<TObjectPtr<UThematicUIButton>> Buttons;
	SelectionButtonsMap.GetKeys(Buttons);
	
	for (UThematicUIButton* Button : Buttons)
	{
		Button->OnTuiButtonPressedAndReleased.RemoveDynamic(this, &ThisClass::HandleOptionSelected);
	}
	
	RemoveFromParent();
}

void UThematicUIDropDownMenuSelection::UpdatePosition()
{
	if (!OwningDropDownMenuRef)
	{
		return;
	}

	FVector2D PixelPosition;
	FVector2D ViewportPosition;
	USlateBlueprintLibrary::LocalToViewport(GetWorld(), OwningDropDownMenuRef->GetTickSpaceGeometry(), FVector2D::ZeroVector, PixelPosition, ViewportPosition);
	FVector2D SelectionMenuPosition = ViewportPosition;
	SelectionMenuPosition.X += (OwningDropDownMenuRef->GetSizeBoxSize().X / 2.0f) - (GetSizeBoxSize().X / 2.0f);
	
	SelectionMenuPosition.Y += OwningDropDownMenuRef->GetSizeBoxSize().Y;
	SetRenderTranslation(SelectionMenuPosition);
}

void UThematicUIDropDownMenuSelection::NativeCreated(UThematicUIDropDownMenu* OwnerMenu, TArray<FText>& OptionsArray, const FThematicUISelectionMenuData& NewData)
{
	OwningDropDownMenuRef = OwnerMenu;
	
	Options = OptionsArray;
	
	SelectionMenuData = NewData;
	
	SetPrimaryWidgetData(SelectionMenuData.SelectionMenuWidgetThemeData);
	
	SetSizeBoxSize(SelectionMenuData.SelectionMenuSize);
	
	switch (SelectionMenuData.SelectionMenuBackground)
	{
		case ESelectionMenuBackground::None:
		{
			BackgroundBlur->SetVisibility(ESlateVisibility::Collapsed);
			BackgroundImage->SetVisibility(ESlateVisibility::Collapsed);
			break;
		}
		case ESelectionMenuBackground::Image:
		{
			BackgroundBlur->SetVisibility(ESlateVisibility::Collapsed);
			BackgroundImage->SetBrush(SelectionMenuData.BackgroundImageBrush);
			break;
		}
		case ESelectionMenuBackground::BackgroundBlur:
		{
			BackgroundBlur->SetBlurStrength(SelectionMenuData.BackgroundBlurStrength);
			BackgroundImage->SetVisibility(ESlateVisibility::Collapsed);
			break;
		}
	}
	
	UpdatePosition();
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
