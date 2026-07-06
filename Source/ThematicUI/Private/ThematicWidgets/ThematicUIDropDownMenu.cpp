// Fill out your copyright notice in the Description page of Project Settings.



// Includes
	// Compiler Includes
	#include "ThematicWidgets/ThematicUIDropDownMenu.h"

	// Engine Library Includes


	// Project Library Includes
	

	// Class Specific Includes
#include "Blueprint/SlateBlueprintLibrary.h"
	#include "Components/Image.h"
	#include "Sound/SoundBase.h"
	#include "ThematicWidgets/ThematicUIButton.h"
	#include "ThematicWidgets/ThematicUIDropDownMenuSelection.h"


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

void UThematicUIDropDownMenu::SetSelectionMenuWidgetThemeData(const FThematicUIMainWidgetData& NewSelectionMenuWidgetThemeData)
{
	SelectionMenuWidgetThemeData = NewSelectionMenuWidgetThemeData;
}

void UThematicUIDropDownMenu::SetSelectionMenuSize(const FVector2D& NewSelectionMenuSize)
{
	SelectionMenuSize = NewSelectionMenuSize;
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
	SelectionMenu->SetPrimaryWidgetData(SelectionMenuWidgetThemeData);
	SelectionMenu->NativeCreated(this, Options);
	
	
	FVector2D PixelPosition;
	FVector2D ViewportPosition;
	USlateBlueprintLibrary::LocalToViewport(GetWorld(), GetTickSpaceGeometry(), FVector2D::ZeroVector, PixelPosition, ViewportPosition);
	FVector2D SelectionMenuPosition = ViewportPosition;
	SelectionMenuPosition.X += (GetSizeBoxSize().X / 2.0f) - (SelectionMenuSize.X / 2.0f);
	
	SelectionMenuPosition.Y += GetSizeBoxSize().Y;
	SelectionMenu->SetRenderTranslation(SelectionMenuPosition);
	
	SelectionMenu->SetSizeBoxSize(SelectionMenuSize);
	
	SelectionMenu->OnTuiOnOptionSelected.AddUniqueDynamic(this, &UThematicUIDropDownMenu::HandleOptionSelected);
}

void UThematicUIDropDownMenu::HandleOptionSelected(int SelectedOptionIndex)
{
	if (Options.IsValidIndex(SelectedOptionIndex))
	{
		SelectedIndex = SelectedOptionIndex;
		
		OnTUiOnSelectionChanged.Broadcast(Options[SelectedIndex], SelectedIndex);
	}
	
	SelectionMenu->OnTuiOnOptionSelected.RemoveDynamic(this, &UThematicUIDropDownMenu::HandleOptionSelected);
	
	if (DropDownButton)
	{
		DropDownButton->SetUserFocus(GetOwningPlayer());
	}
	
	SelectionMenu->RemoveFromParent();
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
	
	// Setup Defaults
	DropDownButton->SetPrimaryWidgetData(GetPrimaryWidgetData());
	if (DropDownArrowImage)
	{
		DropDownArrowImage->SetBrush(DropDownArrowBrush);
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
