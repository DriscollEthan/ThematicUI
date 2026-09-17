// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/ThematicUiButton.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

const FText& UThematicUiButton::GetText() const
{
	return Text;
}

void UThematicUiButton::SetText(const FText& value)
{
	Text = value;
	
	if (TextBlock)
	{
		TextBlock->SetText(Text);
	}
}

bool UThematicUiButton::TuiHasUserFocus()
{
	return Button->HasAnyUserFocus();
}

void UThematicUiButton::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (TextBlock)
	{
		TextBlock->SetText(Text);
	}
}

void UThematicUiButton::NativeConstruct()
{
	Super::NativeConstruct();
	
	Button->OnPressed.AddUniqueDynamic(this, &ThisClass::HandleButtonPressed);
	Button->OnReleased.AddUniqueDynamic(this, &ThisClass::HandleButtonReleased);
}

FReply UThematicUiButton::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	if (Button)
	{
		return FReply::Handled().SetUserFocus(Button->TakeWidget(), InFocusEvent.GetCause());
	}

	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

void UThematicUiButton::SetThemeNormal()
{
	Super::SetThemeNormal();
	
	if (Button && TextBlock) [[likely]]
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
		UE_LOGFMT(LogThematicUI, Error, "UThematicUiButton::SetThemeNormal : UThematicUiButton::Button == nullptr || UThematicUiButton::TextBlock == nullptr");
	}
}

void UThematicUiButton::SetThemeHovered()
{
	Super::SetThemeHovered();
	
	if (Button && TextBlock) [[likely]]
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
		UE_LOGFMT(LogThematicUI, Error, "UThematicUiButton::SetThemeNormal : UThematicUiButton::Button == nullptr || UThematicUiButton::TextBlock == nullptr");
	}
}

void UThematicUiButton::SetThemePressed()
{
	Super::SetThemePressed();
	
	if (Button && TextBlock) [[likely]]
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
		UE_LOGFMT(LogThematicUI, Error, "UThematicUiButton::SetThemeNormal : UThematicUiButton::Button == nullptr || UThematicUiButton::TextBlock == nullptr");
	}
}

void UThematicUiButton::HandleButtonPressed()
{
	if (Button->HasAnyUserFocus())
		SetThemePressed();
}

void UThematicUiButton::HandleButtonReleased()
{
	if (Button->HasAnyUserFocus())
	{
		SetThemeHovered();
		
		OnTuiButtonPressedAndReleased.Broadcast(this);
	}
}
