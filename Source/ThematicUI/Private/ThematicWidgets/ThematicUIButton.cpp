// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/ThematicUIButton.h"

#include "Components/SizeBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"


void UThematicUIButton::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(SizeBoxSize.X);
		SizeBox->SetHeightOverride(SizeBoxSize.Y);
	}
	if (TextBlock)
	{
		TextBlock->SetText(Text);
	}
}

void UThematicUIButton::NativeConstruct()
{
	Super::NativeConstruct();
	
	Button->OnPressed.AddUniqueDynamic(this, &ThisClass::HandleButtonPressed);
	Button->OnReleased.AddUniqueDynamic(this, &ThisClass::HandleButtonReleased);
}

FReply UThematicUIButton::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	if (Button)
	{
		return FReply::Handled().SetUserFocus(Button->TakeWidget(), InFocusEvent.GetCause());
	}

	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

void UThematicUIButton::SetThemeNormal()
{
	Super::SetThemeNormal();
	
	if (Button && TextBlock && WidgetTheme) [[likely]]
	{
		// Create Button Style to Change
		FButtonStyle Style;

		// Set Image Settings / SlateBrush
		Style.SetNormal(ActualThemeData.NormalTheme.Image);
		Style.SetHovered(ActualThemeData.NormalTheme.Image);
		Style.SetPressed(ActualThemeData.NormalTheme.Image);
	
		// Set Sounds
		Style.SetHoveredSound(ActualThemeData.HoveredTheme.Sound);
		Style.SetPressedSound(ActualThemeData.PressedTheme.Sound);
	
		// Set Button Style
		Button->SetStyle(Style);
	
		//Set Text Style
		TextBlock->SetFont(ActualThemeData.NormalTheme.TextFont);
		TextBlock->SetColorAndOpacity(ActualThemeData.NormalTheme.TextColor);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUIButton::SetThemeNormal : UThematicUIButton::Button == nullptr || UThematicUIButton::TextBlock == nullptr || UThematicUIButton::WidgetTheme == nullptr");
	}
}

void UThematicUIButton::SetThemeHovered()
{
	Super::SetThemeHovered();
	
	if (Button && TextBlock && WidgetTheme) [[likely]]
	{
		// Create Button Style to Change
		FButtonStyle Style;

		// Set Image Settings / SlateBrush
		Style.SetNormal(ActualThemeData.HoveredTheme.Image);
		Style.SetHovered(ActualThemeData.HoveredTheme.Image);
		Style.SetPressed(ActualThemeData.HoveredTheme.Image);
	
		// Set Sounds
		Style.SetHoveredSound(ActualThemeData.HoveredTheme.Sound);
		Style.SetPressedSound(ActualThemeData.PressedTheme.Sound);
	
		// Set Button Style
		Button->SetStyle(Style);
	
		//Set Text Style
		TextBlock->SetColorAndOpacity(ActualThemeData.HoveredTheme.TextColor);
		TextBlock->SetFont(ActualThemeData.HoveredTheme.TextFont);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUIButton::SetThemeNormal : UThematicUIButton::Button == nullptr || UThematicUIButton::TextBlock == nullptr || UThematicUIButton::WidgetTheme == nullptr");
	}
}

void UThematicUIButton::SetThemePressed()
{
	Super::SetThemePressed();
	
	if (Button && TextBlock && WidgetTheme) [[likely]]
	{
		// Create Button Style to Change
		FButtonStyle Style;

		// Set Image Settings / SlateBrush
		Style.SetNormal(ActualThemeData.PressedTheme.Image);
		Style.SetHovered(ActualThemeData.PressedTheme.Image);
		Style.SetPressed(ActualThemeData.PressedTheme.Image);
	
		// Set Sounds
		Style.SetHoveredSound(ActualThemeData.HoveredTheme.Sound);
		Style.SetPressedSound(ActualThemeData.PressedTheme.Sound);
	
		// Set Button Style
		Button->SetStyle(Style);
	
		//Set Text Style
		TextBlock->SetColorAndOpacity(ActualThemeData.PressedTheme.TextColor);
		TextBlock->SetFont(ActualThemeData.PressedTheme.TextFont);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUIButton::SetThemeNormal : UThematicUIButton::Button == nullptr || UThematicUIButton::TextBlock == nullptr || UThematicUIButton::WidgetTheme == nullptr");
	}
}

void UThematicUIButton::HandleButtonPressed()
{
	if (Button->HasAnyUserFocus())
		SetThemePressed();
}

void UThematicUIButton::HandleButtonReleased()
{
	if (Button->HasAnyUserFocus())
	{
		SetThemeHovered();
		TUiButtonPressed.Broadcast();
	}
}
