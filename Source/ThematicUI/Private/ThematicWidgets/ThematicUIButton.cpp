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
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUIButton::NativePreConstruct : UThematicUIButton::ThemedSizeBox == nullptr");
	}
	if (TextBlock)
	{
		TextBlock->SetText(Text);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUIButton::NativePreConstruct : UThematicUIButton::TextBlock == nullptr");
	}
	
	SetThemeNormal();
}

void UThematicUIButton::NativeConstruct()
{
	Super::NativeConstruct();
	
	Button->OnPressed.AddUniqueDynamic(this, &ThisClass::HandleButtonPressed);
	Button->OnReleased.AddUniqueDynamic(this, &ThisClass::HandleButtonReleased);
}

void UThematicUIButton::SetThemeNormal()
{
	Super::SetThemeNormal();
	
	if (Button && TextBlock && WidgetTheme)
	{
		// Create Button Style to Change
		FButtonStyle Style;

		// Set Image Settings / SlateBrush
		Style.SetNormal(WidgetTheme->NormalTheme.Image);
		Style.SetHovered(WidgetTheme->NormalTheme.Image);
		Style.SetPressed(WidgetTheme->NormalTheme.Image);
	
		// Set Sounds
		Style.SetHoveredSound(WidgetTheme->NormalTheme.Sound);
		Style.SetPressedSound(WidgetTheme->NormalTheme.Sound);
	
		// Set Button Style
		Button->SetStyle(Style);
	
		//Set Text Style
		TextBlock->SetColorAndOpacity(WidgetTheme->NormalTheme.TextColor);
		TextBlock->SetFont(WidgetTheme->NormalTheme.TextFont);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUIButton::SetThemeNormal : UThematicUIButton::Button == nullptr || UThematicUIButton::TextBlock == nullptr || UThematicUIButton::WidgetTheme == nullptr");
	}
}

void UThematicUIButton::SetThemeHovered()
{
	Super::SetThemeHovered();
	
	if (Button && TextBlock && WidgetTheme)
	{
		// Create Button Style to Change
		FButtonStyle Style;

		// Set Image Settings / SlateBrush
		Style.SetNormal(WidgetTheme->HoveredTheme.Image);
		Style.SetHovered(WidgetTheme->HoveredTheme.Image);
		Style.SetPressed(WidgetTheme->HoveredTheme.Image);
	
		// Set Sounds
		Style.SetHoveredSound(WidgetTheme->HoveredTheme.Sound);
		Style.SetPressedSound(WidgetTheme->HoveredTheme.Sound);
	
		// Set Button Style
		Button->SetStyle(Style);
	
		//Set Text Style
		TextBlock->SetColorAndOpacity(WidgetTheme->HoveredTheme.TextColor);
		TextBlock->SetFont(WidgetTheme->HoveredTheme.TextFont);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUIButton::SetThemeNormal : UThematicUIButton::Button == nullptr || UThematicUIButton::TextBlock == nullptr || UThematicUIButton::WidgetTheme == nullptr");
	}
}

void UThematicUIButton::SetThemePressed()
{
	Super::SetThemePressed();
	
	if (Button && TextBlock && WidgetTheme)
	{
		// Create Button Style to Change
		FButtonStyle Style;

		// Set Image Settings / SlateBrush
		Style.SetNormal(WidgetTheme->PressedTheme.Image);
		Style.SetHovered(WidgetTheme->PressedTheme.Image);
		Style.SetPressed(WidgetTheme->PressedTheme.Image);
	
		// Set Sounds
		Style.SetHoveredSound(WidgetTheme->PressedTheme.Sound);
		Style.SetPressedSound(WidgetTheme->PressedTheme.Sound);
	
		// Set Button Style
		Button->SetStyle(Style);
	
		//Set Text Style
		TextBlock->SetColorAndOpacity(WidgetTheme->PressedTheme.TextColor);
		TextBlock->SetFont(WidgetTheme->PressedTheme.TextFont);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUIButton::SetThemeNormal : UThematicUIButton::Button == nullptr || UThematicUIButton::TextBlock == nullptr || UThematicUIButton::WidgetTheme == nullptr");
	}
}

void UThematicUIButton::HandleButtonPressed()
{
	SetThemePressed();
}

void UThematicUIButton::HandleButtonReleased()
{
	SetThemeHovered();
	TUiButtonPressedDelegate.Broadcast();
}
