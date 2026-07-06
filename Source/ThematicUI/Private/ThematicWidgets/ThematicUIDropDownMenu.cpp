// Fill out your copyright notice in the Description page of Project Settings.



// Includes
	// Compiler Includes
	#include "ThematicWidgets/ThematicUIDropDownMenu.h"

	// Engine Library Includes


	// Project Library Includes
	

	// Class Specific Includes
	#include "Components/Image.h"
	#include "Sound/SoundBase.h"
	#include "ThematicWidgets/ThematicUIButton.h"
	#include "ThematicWidgets/ThematicUIDropDownMenuSelection.h"


const FThematicUIThemeDataOverride& UThematicUIDropDownMenu::GetSelectionMenuWidgetThemeOverrideData() const
{
	return SelectionMenuWidgetThemeOverrideData;
}

void UThematicUIDropDownMenu::SetSelectionMenuWidgetThemeOverrideData(const FThematicUIThemeDataOverride& NewWidgetThemeOverrideData)
{
	SelectionMenuWidgetThemeOverrideData = NewWidgetThemeOverrideData;
	
	SelectionMenuCalculateAndSetActualWidgetThemeData();
}

void UThematicUIDropDownMenu::SetSelectionMenuWidgetNormalThemeOverrideDate(const FThematicUIThemeOverride& NewWidgetNormalThemeOverride)
{
	SelectionMenuWidgetThemeOverrideData.NormalThemeOverride = NewWidgetNormalThemeOverride;
	
	SelectionMenuCalculateAndSetActualWidgetThemeData();
}

void UThematicUIDropDownMenu::SetSelectionMenuWidgetHoveredThemeOverrideDate(const FThematicUIThemeOverride& NewWidgetHoveredThemeOverride)
{
	SelectionMenuWidgetThemeOverrideData.HoveredThemeOverride = NewWidgetHoveredThemeOverride;
	
	SelectionMenuCalculateAndSetActualWidgetThemeData();
}

void UThematicUIDropDownMenu::SetSelectionMenuWidgetPressedThemeOverrideDate(const FThematicUIThemeOverride& NewWidgetPressedThemeOverride)
{
	SelectionMenuWidgetThemeOverrideData.PressedThemeOverride = NewWidgetPressedThemeOverride;
	
	SelectionMenuCalculateAndSetActualWidgetThemeData();
}

const FThematicUIThemeData& UThematicUIDropDownMenu::GetSelectionMenuActualThemeData() const
{
	return SelectionMenuActualThemeData;
}

void UThematicUIDropDownMenu::SelectionMenuCalculateAndSetActualWidgetThemeData()
{
// Figure Out ActualThemeData after overrides
	if (SelectionMenuWidgetTheme)
	{
		SelectionMenuActualThemeData = SelectionMenuWidgetThemeOverrideData.ConvertToThemeData(SelectionMenuWidgetTheme->GetThematicUIThemeData());
	}
	else
	{
		SelectionMenuActualThemeData = WidgetThemeOverrideData.ConvertToThemeData();
	}
}

const FVector2D& UThematicUIDropDownMenu::GetSelectionMenuSizeBoxSize() const
{
	return SelectionMenuSizeBoxSize;
}

void UThematicUIDropDownMenu::SetSelectionMenuSizeBoxSize(const FVector2D& NewSizeBoxSize)
{
	SelectionMenuSizeBoxSize = NewSizeBoxSize;
	
	// @todo CALL SETSIZEBOXSIZE ON Options Menu
}

void UThematicUIDropDownMenu::HandleDropDownButtonPressed()
{
	// @todo Creation and Setup Options Logic
	
	SelectionMenu = CreateWidget<UThematicUIDropDownMenuSelection>(this, SelectionMenuSubclass, NAME_None);
	SelectionMenu->AddToViewport(100);
	SelectionMenu->SetOwningPlayer(GetOwningPlayer());
	
	SelectionMenu->SetWidgetThemeOverrideData(FThematicUIThemeDataOverride::ForceToThemeOverrideData(SelectionMenuActualThemeData));
	SelectionMenu->SetSizeBoxSize(SelectionMenuSizeBoxSize);
	
	
	SelectionMenu->SetRenderTranslation(GetCachedGeometry().LocalToAbsolute(FVector2D::ZeroVector) + FVector2D(0.0f, GetSizeBoxSize().Y));
}

void UThematicUIDropDownMenu::HandleOptionSelected(FText SelectedOption, int SelectedIndex)
{

}

void UThematicUIDropDownMenu::SetThemeNormal()
{
	Super::SetThemeNormal();
}

void UThematicUIDropDownMenu::SetThemeHovered()
{
	Super::SetThemeHovered();
}

void UThematicUIDropDownMenu::SetThemePressed()
{
	Super::SetThemePressed();
}

void UThematicUIDropDownMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UThematicUIDropDownMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

FReply UThematicUIDropDownMenu::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}
