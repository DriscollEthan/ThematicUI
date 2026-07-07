// Fill out your copyright notice in the Description page of Project Settings.



// Includes
	// Compiler Includes
	#include "ThematicWidgets/ThematicUIDropDownMenu.h"

	// Engine Library Includes


	// Project Library Includes
	

	// Class Specific Includes
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Image.h"
#include "Components/OverlaySlot.h"
#include "Sound/SoundBase.h"
	#include "ThematicWidgets/ThematicUIButton.h"
	#include "ThematicWidgets/ThematicUIDropDownMenuSelection.h"


void UThematicUIDropDownMenu::SetOptions(const TArray<FText>& NewOptions)
{
	Options = NewOptions;
} 

const FSlateBrush& UThematicUIDropDownMenu::GetDropDownArrowBrush() const
{
	return DropDownArrowBrush;
}

void UThematicUIDropDownMenu::SetDropDownArrowBrush(const FSlateBrush& NewDropDownArrowBrush)
{
	DropDownArrowBrush = NewDropDownArrowBrush;
	
	if (DropDownArrowImage)
	{
		DropDownArrowImage->SetBrush(DropDownArrowBrush);
	}
}

const int UThematicUIDropDownMenu::GetSelectedOption(FText& SelectedOption) const
{
	if (Options.IsValidIndex(SelectedIndex))
	{
		SelectedOption = Options[SelectedIndex];
	}
	return SelectedIndex;
}

const FThematicUIMainWidgetData& UThematicUIDropDownMenu::GetSelectionMenuWidgetThemeData() const
{
	return SelectionMenuData.SelectionMenuWidgetThemeData;
}

void UThematicUIDropDownMenu::SetSelectionMenuWidgetThemeData(const FThematicUIMainWidgetData& NewSelectionMenuWidgetThemeData)
{
	SelectionMenuData.SelectionMenuWidgetThemeData = NewSelectionMenuWidgetThemeData;
}

const FVector2D& UThematicUIDropDownMenu::GetSelectionMenuSize() const
{
	return SelectionMenuData.SelectionMenuSize;
}

void UThematicUIDropDownMenu::SetSelectionMenuSize(const FVector2D& NewSelectionMenuSize)
{
	SelectionMenuData.SelectionMenuSize = NewSelectionMenuSize;
}

const FMargin& UThematicUIDropDownMenu::GetSelectionMenuOptionsPadding() const
{	
	return SelectionMenuData.SelectionMenuOptionsPadding;
}

void UThematicUIDropDownMenu::SetSelectionMenuOptionsPadding(const FMargin& NewSelectionMenuOptionsPadding)
{
	SelectionMenuData.SelectionMenuOptionsPadding = NewSelectionMenuOptionsPadding;
}

void UThematicUIDropDownMenu::HandleDropDownButtonPressed(UThematicUIButton* PressedButton)
{
	// @todo Creation and Setup Options Logic
	if (!SelectionMenuSubclass->IsValidLowLevel() || DropDownButton != PressedButton)
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUIDropDownMenu::HandleDropDownButtonPressed(), {Name}::SelectionMenuSubclass is INVALID", GetName());
		return;
	}
	
	SelectionMenu = CreateWidget<UThematicUIDropDownMenuSelection>(GetOwningPlayer(), SelectionMenuSubclass, NAME_None);
	
	verifyf(SelectionMenu->IsValidLowLevel(), TEXT("UThematicUIDropDownMenu::HandleDropDownButtonPressed, SelectionMenu == nullptr || Failed To Create"));
	
	SelectionMenu->AddToViewport(100);
	SelectionMenu->SetOwningPlayer(GetOwningPlayer());
	SelectionMenu->NativeCreated(this, Options, SelectionMenuData);
	
	SelectionMenu->OnTuiOnOptionSelected.AddUniqueDynamic(this, &UThematicUIDropDownMenu::HandleOptionSelected);
}

void UThematicUIDropDownMenu::HandleOptionSelected(int SelectedOptionIndex)
{
	// BTW THE SelectionMenu WILL DESTROY ITSELF AFTER THIS

	if (Options.IsValidIndex(SelectedOptionIndex))
	{
		SelectedIndex = SelectedOptionIndex;
		
		DropDownButton->SetText(Options[SelectedIndex]);
		
		OnTUiOnSelectionChanged.Broadcast(Options[SelectedIndex], SelectedIndex);
	}
	
	if (SelectionMenu)
	{
	SelectionMenu->OnTuiOnOptionSelected.RemoveDynamic(this, &UThematicUIDropDownMenu::HandleOptionSelected);
	}
	
	if (DropDownButton)
	{
		DropDownButton->SetUserFocus(GetOwningPlayer());
	}
}

void UThematicUIDropDownMenu::SetThemeNormal()
{
	Super::SetThemeNormal();
	
	if (DropDownButton)
	{
		DropDownButton->SetThemeNormal();
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUIDropDownMenu::SetThemeNormal : UThematicUIDropDownMenu::DropDownButton == nullptr");
	}
}

void UThematicUIDropDownMenu::SetThemeHovered()
{
	Super::SetThemeHovered();
	
	if (DropDownButton)
	{
		DropDownButton->SetThemeHovered();
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUIDropDownMenu::SetThemeHovered : UThematicUIDropDownMenu::DropDownButton == nullptr");
	}
}

void UThematicUIDropDownMenu::SetThemePressed()
{
	Super::SetThemePressed();
	
	if (DropDownButton)
	{
		DropDownButton->SetThemePressed();
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUIDropDownMenu::SetThemePressed : UThematicUIDropDownMenu::DropDownButton == nullptr");
	}
}

void UThematicUIDropDownMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	// Setup Defaults
	if (DropDownButton)
	{
		DropDownButton->SetPrimaryWidgetData(GetPrimaryWidgetData());
		DropDownButton->SetThemeNormal();
		
		if (Options.IsValidIndex(0))
		{
			DropDownButton->SetText(Options[0]);
		}
	}
	
	if (DropDownArrowImage)
	{
		DropDownArrowImage->SetBrush(DropDownArrowBrush);
		
		if (UOverlaySlot* OverlaySlot = UWidgetLayoutLibrary::SlotAsOverlaySlot(DropDownArrowImage))
		{
			OverlaySlot->SetPadding(FMargin(0.0f, 0.0f, ActualThemeData.NormalTheme.Image.OutlineSettings.Width + 2.0f, 0.0f));
		}
	}
}

void UThematicUIDropDownMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	
	// Bind to Delegates
	DropDownButton->OnTuiButtonPressedAndReleased.AddUniqueDynamic(this, &UThematicUIDropDownMenu::HandleDropDownButtonPressed);
}

FReply UThematicUIDropDownMenu::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	if (DropDownButton)
	{
		return FReply::Handled().SetUserFocus(DropDownButton->TakeWidget(), InFocusEvent.GetCause());
	}
	
	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

void UThematicUIDropDownMenu::NativeDestruct()
{
	Super::NativeDestruct();
	
	DropDownButton->OnTuiButtonPressedAndReleased.RemoveDynamic(this, &UThematicUIDropDownMenu::HandleDropDownButtonPressed);
}
