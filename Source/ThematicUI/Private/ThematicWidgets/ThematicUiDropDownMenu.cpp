// Fill out your copyright notice in the Description page of Project Settings.



// Includes
	// Compiler Includes
	#include "ThematicWidgets/ThematicUiDropDownMenu.h"

// Engine Library Includes


	// Project Library Includes
	

	// Class Specific Includes
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Image.h"
#include "Components/OverlaySlot.h"
#include "Sound/SoundBase.h"
	#include "ThematicWidgets/ThematicUiButton.h"
#include "ThematicWidgets/ThematicUiDropDownMenuSelection.h"


void UThematicUiDropDownMenu::SetOptions(const TArray<FText>& NewOptions)
{
	Options = NewOptions;
} 

const FSlateBrush& UThematicUiDropDownMenu::GetDropDownArrowBrush() const
{
	return DropDownArrowBrush;
}

void UThematicUiDropDownMenu::SetDropDownArrowBrush(const FSlateBrush& NewDropDownArrowBrush)
{
	DropDownArrowBrush = NewDropDownArrowBrush;
	
	if (DropDownArrowImage)
	{
		DropDownArrowImage->SetBrush(DropDownArrowBrush);
	}
}

const int UThematicUiDropDownMenu::GetSelectedOption(FText& SelectedOption) const
{
	if (Options.IsValidIndex(SelectedIndex))
	{
		SelectedOption = Options[SelectedIndex];
	}
	return SelectedIndex;
}

const FThematicUIMainWidgetData& UThematicUiDropDownMenu::GetSelectionMenuWidgetThemeData() const
{
	return SelectionMenuData.SelectionMenuWidgetThemeData;
}

void UThematicUiDropDownMenu::SetSelectionMenuWidgetThemeData(const FThematicUIMainWidgetData& NewSelectionMenuWidgetThemeData)
{
	SelectionMenuData.SelectionMenuWidgetThemeData = NewSelectionMenuWidgetThemeData;
}

const FVector2D& UThematicUiDropDownMenu::GetSelectionMenuSize() const
{
	return SelectionMenuData.SelectionMenuSize;
}

void UThematicUiDropDownMenu::SetSelectionMenuSize(const FVector2D& NewSelectionMenuSize)
{
	SelectionMenuData.SelectionMenuSize = NewSelectionMenuSize;
}

const FMargin& UThematicUiDropDownMenu::GetSelectionMenuOptionsPadding() const
{	
	return SelectionMenuData.SelectionMenuOptionsPadding;
}

void UThematicUiDropDownMenu::SetSelectionMenuOptionsPadding(const FMargin& NewSelectionMenuOptionsPadding)
{
	SelectionMenuData.SelectionMenuOptionsPadding = NewSelectionMenuOptionsPadding;
}

void UThematicUiDropDownMenu::HandleDropDownButtonPressed(UThematicUiButton* PressedButton)
{
	// @todo Creation and Setup Options Logic
	if (!SelectionMenuSubclass->IsValidLowLevel() || DropDownButton != PressedButton)
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUiDropDownMenu::HandleDropDownButtonPressed(), {Name}::SelectionMenuSubclass is INVALID", GetName());
		return;
	}
	
	SelectionMenu = CreateWidget<UThematicUiDropDownMenuSelection>(GetOwningPlayer(), SelectionMenuSubclass, NAME_None);
	
	verifyf(SelectionMenu->IsValidLowLevel(), TEXT("UThematicUiDropDownMenu::HandleDropDownButtonPressed, SelectionMenu == nullptr || Failed To Create"));
	
	SelectionMenu->AddToViewport(100);
	SelectionMenu->SetOwningPlayer(GetOwningPlayer());
	SelectionMenu->NativeCreated(this, Options, SelectionMenuData);
	
	SelectionMenu->OnTuiOnOptionSelected.AddUniqueDynamic(this, &UThematicUiDropDownMenu::HandleOptionSelected);
}

void UThematicUiDropDownMenu::HandleOptionSelected(int SelectedOptionIndex)
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
	SelectionMenu->OnTuiOnOptionSelected.RemoveDynamic(this, &UThematicUiDropDownMenu::HandleOptionSelected);
	}
	
	if (DropDownButton)
	{
		DropDownButton->SetUserFocus(GetOwningPlayer());
	}
}

void UThematicUiDropDownMenu::SetThemeNormal()
{
	Super::SetThemeNormal();
	
	if (DropDownButton)
	{
		DropDownButton->SetThemeNormal();
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUiDropDownMenu::SetThemeNormal : UThematicUiDropDownMenu::DropDownButton == nullptr");
	}
}

void UThematicUiDropDownMenu::SetThemeHovered()
{
	Super::SetThemeHovered();
	
	if (DropDownButton)
	{
		DropDownButton->SetThemeHovered();
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUiDropDownMenu::SetThemeHovered : UThematicUiDropDownMenu::DropDownButton == nullptr");
	}
}

void UThematicUiDropDownMenu::SetThemePressed()
{
	Super::SetThemePressed();
	
	if (DropDownButton)
	{
		DropDownButton->SetThemePressed();
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUiDropDownMenu::SetThemePressed : UThematicUiDropDownMenu::DropDownButton == nullptr");
	}
}

void UThematicUiDropDownMenu::NativePreConstruct()
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

void UThematicUiDropDownMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	
	// Bind to Delegates
	DropDownButton->OnTuiButtonPressedAndReleased.AddUniqueDynamic(this, &UThematicUiDropDownMenu::HandleDropDownButtonPressed);
}

FReply UThematicUiDropDownMenu::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	if (DropDownButton)
	{
		return FReply::Handled().SetUserFocus(DropDownButton->TakeWidget(), InFocusEvent.GetCause());
	}
	
	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

void UThematicUiDropDownMenu::NativeDestruct()
{
	Super::NativeDestruct();
	
	DropDownButton->OnTuiButtonPressedAndReleased.RemoveDynamic(this, &UThematicUiDropDownMenu::HandleDropDownButtonPressed);
}
