// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/ThematicUIDropDownMenu.h"

#include "Components/ComboBoxString.h"
#include "Components/SizeBox.h"

void UThematicUIDropDownMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(SizeBoxSize.X);
		SizeBox->SetHeightOverride(SizeBoxSize.Y);
	}
	if (ComboBoxString)
	{
		ComboBoxString->ClearOptions();
		for (auto& option : Options)
		{
			ComboBoxString->AddOption(option);
		}
		
		if (Options.IsValidIndex(0))
			ComboBoxString->SetSelectedOption(Options[0]);
	}
	
	SetThemeNormal();
}

void UThematicUIDropDownMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (ComboBoxString)
	{
		ComboBoxString->OnOpening.AddUniqueDynamic(this, &UThematicUIDropDownMenu::UThematicUIDropDownMenu::HandleOpening);
		ComboBoxString->OnSelectionChanged.AddUniqueDynamic(this, &UThematicUIDropDownMenu::HandleSelectionChanged);
;	}
}

FReply UThematicUIDropDownMenu::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	if (ComboBoxString)
	{
		return FReply::Handled().SetUserFocus(ComboBoxString->TakeWidget(), InFocusEvent.GetCause());
	}
	
	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

void UThematicUIDropDownMenu::SetThemeNormal()
{
	Super::SetThemeNormal();
	
	if (ComboBoxString && WidgetTheme)
	{
		FComboBoxStyle DropDownStyle;
		FTableRowStyle DropDownRowStyle;
		FSlateBrush ItemStyleNormalImage = WidgetTheme->NormalTheme.Image;
		ItemStyleNormalImage.OutlineSettings.Width = -100.0f;
		ItemStyleNormalImage.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
		FSlateBrush ItemStyleHoveredImage = WidgetTheme->HoveredTheme.Image;
		ItemStyleHoveredImage.OutlineSettings.Width = -100.0f;
		ItemStyleHoveredImage.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
		FSlateBrush ItemStylePressedImage = WidgetTheme->PressedTheme.Image;
		ItemStylePressedImage.OutlineSettings.Width = -100.0f;
		ItemStylePressedImage.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
		
		DropDownStyle.ComboButtonStyle.ButtonStyle.Normal = WidgetTheme->NormalTheme.Image;
		DropDownStyle.ComboButtonStyle.ButtonStyle.Hovered = WidgetTheme->NormalTheme.Image;
		DropDownStyle.ComboButtonStyle.ButtonStyle.Pressed = WidgetTheme->NormalTheme.Image;
		DropDownStyle.ComboButtonStyle.DownArrowImage = DropDownArrowBrush;
		DropDownStyle.ComboButtonStyle.DownArrowImage.TintColor = WidgetTheme->NormalTheme.Image.OutlineSettings.Color;
		
		DropDownRowStyle.SelectorFocusedBrush.TintColor.GetSpecifiedColor() = WidgetTheme->NormalTheme.FillColor;
		DropDownRowStyle.EvenRowBackgroundBrush = ItemStyleNormalImage;
		DropDownRowStyle.OddRowBackgroundBrush = ItemStyleNormalImage;
		DropDownRowStyle.EvenRowBackgroundHoveredBrush = ItemStyleHoveredImage;
		DropDownRowStyle.OddRowBackgroundHoveredBrush = ItemStyleHoveredImage;
		DropDownRowStyle.TextColor = WidgetTheme->NormalTheme.TextColor;
		DropDownRowStyle.SelectedTextColor = WidgetTheme->PressedTheme.TextColor;
		DropDownRowStyle.ActiveBrush = ItemStyleHoveredImage;
		DropDownRowStyle.ActiveHoveredBrush = ItemStylePressedImage;
		DropDownRowStyle.ParentRowBackgroundBrush = ItemStyleNormalImage;
		DropDownRowStyle.ParentRowBackgroundHoveredBrush = ItemStyleHoveredImage;
		DropDownRowStyle.SelectorFocusedBrush = ItemStyleNormalImage;
		
		ComboBoxString->SetWidgetStyle(DropDownStyle);
		ComboBoxString->SetItemStyle(DropDownRowStyle);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUIDropDownMenu::SetThemeNormal : UThematicUIButton::ComboBoxKey == nullptr || UThematicUIButton::WidgetTheme == nullptr");
	}
}

void UThematicUIDropDownMenu::SetThemeHovered()
{
	Super::SetThemeHovered();
	
	if (ComboBoxString && WidgetTheme)
	{
		FComboBoxStyle DropDownStyle;
		FTableRowStyle DropDownRowStyle;
		FSlateBrush ItemStyleNormalImage = WidgetTheme->NormalTheme.Image;
		ItemStyleNormalImage.OutlineSettings.Width = -100.0f;
		ItemStyleNormalImage.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
		FSlateBrush ItemStyleHoveredImage = WidgetTheme->HoveredTheme.Image;
		ItemStyleHoveredImage.OutlineSettings.Width = -100.0f;
		ItemStyleHoveredImage.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
		FSlateBrush ItemStylePressedImage = WidgetTheme->PressedTheme.Image;
		ItemStylePressedImage.OutlineSettings.Width = -100.0f;
		ItemStylePressedImage.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
		
		DropDownStyle.ComboButtonStyle.ButtonStyle.Normal = WidgetTheme->HoveredTheme.Image;
		DropDownStyle.ComboButtonStyle.ButtonStyle.Hovered = WidgetTheme->HoveredTheme.Image;
		DropDownStyle.ComboButtonStyle.ButtonStyle.Pressed = WidgetTheme->HoveredTheme.Image;
		DropDownStyle.ComboButtonStyle.DownArrowImage = DropDownArrowBrush;
		DropDownStyle.ComboButtonStyle.DownArrowImage.TintColor = WidgetTheme->HoveredTheme.Image.OutlineSettings.Color;
		
		DropDownRowStyle.SelectorFocusedBrush.TintColor.GetSpecifiedColor() = WidgetTheme->NormalTheme.FillColor;
		DropDownRowStyle.EvenRowBackgroundBrush = ItemStyleNormalImage;
		DropDownRowStyle.OddRowBackgroundBrush = ItemStyleNormalImage;
		DropDownRowStyle.EvenRowBackgroundHoveredBrush = ItemStyleHoveredImage;
		DropDownRowStyle.OddRowBackgroundHoveredBrush = ItemStyleHoveredImage;
		DropDownRowStyle.TextColor = WidgetTheme->NormalTheme.TextColor;
		DropDownRowStyle.SelectedTextColor = WidgetTheme->PressedTheme.TextColor;
		DropDownRowStyle.ActiveBrush = ItemStyleHoveredImage;
		DropDownRowStyle.ActiveHoveredBrush = ItemStylePressedImage;
		DropDownRowStyle.ParentRowBackgroundBrush = ItemStyleNormalImage;
		DropDownRowStyle.ParentRowBackgroundHoveredBrush = ItemStyleHoveredImage;
		DropDownRowStyle.SelectorFocusedBrush = ItemStyleNormalImage;
		
		ComboBoxString->SetWidgetStyle(DropDownStyle);
		ComboBoxString->SetItemStyle(DropDownRowStyle);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUIDropDownMenu::SetThemeHovered : UThematicUIButton::ComboBoxKey == nullptr || UThematicUIButton::WidgetTheme == nullptr");
	}
}

void UThematicUIDropDownMenu::SetThemePressed()
{
	Super::SetThemePressed();
	
	if (ComboBoxString && WidgetTheme)
	{
		FComboBoxStyle DropDownStyle;
		FTableRowStyle DropDownRowStyle;
		FSlateBrush ItemStyleNormalImage = WidgetTheme->NormalTheme.Image;
		ItemStyleNormalImage.OutlineSettings.Width = -100.0f;
		ItemStyleNormalImage.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
		FSlateBrush ItemStyleHoveredImage = WidgetTheme->HoveredTheme.Image;
		ItemStyleHoveredImage.OutlineSettings.Width = -100.0f;
		ItemStyleHoveredImage.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
		FSlateBrush ItemStylePressedImage = WidgetTheme->PressedTheme.Image;
		ItemStylePressedImage.OutlineSettings.Width = -100.0f;
		ItemStylePressedImage.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
		
		DropDownStyle.ComboButtonStyle.ButtonStyle.Normal = WidgetTheme->PressedTheme.Image;
		DropDownStyle.ComboButtonStyle.ButtonStyle.Hovered = WidgetTheme->PressedTheme.Image;
		DropDownStyle.ComboButtonStyle.ButtonStyle.Pressed = WidgetTheme->PressedTheme.Image;
		DropDownStyle.ComboButtonStyle.DownArrowImage = DropDownArrowBrush;
		DropDownStyle.ComboButtonStyle.DownArrowImage.TintColor = WidgetTheme->PressedTheme.Image.OutlineSettings.Color;
		
		DropDownRowStyle.SelectorFocusedBrush.TintColor.GetSpecifiedColor() = WidgetTheme->NormalTheme.FillColor;
		DropDownRowStyle.EvenRowBackgroundBrush = ItemStyleNormalImage;
		DropDownRowStyle.OddRowBackgroundBrush = ItemStyleNormalImage;
		DropDownRowStyle.EvenRowBackgroundHoveredBrush = ItemStyleHoveredImage;
		DropDownRowStyle.OddRowBackgroundHoveredBrush = ItemStyleHoveredImage;
		DropDownRowStyle.TextColor = WidgetTheme->NormalTheme.TextColor;
		DropDownRowStyle.SelectedTextColor = WidgetTheme->PressedTheme.TextColor;
		DropDownRowStyle.ActiveBrush = ItemStyleHoveredImage;
		DropDownRowStyle.ActiveHoveredBrush = ItemStylePressedImage;
		DropDownRowStyle.ParentRowBackgroundBrush = ItemStyleNormalImage;
		DropDownRowStyle.ParentRowBackgroundHoveredBrush = ItemStyleHoveredImage;
		DropDownRowStyle.SelectorFocusedBrush = ItemStyleNormalImage;
		
		ComboBoxString->SetWidgetStyle(DropDownStyle);
		ComboBoxString->SetItemStyle(DropDownRowStyle);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUIDropDownMenu::SetThemePressed : UThematicUIButton::ComboBoxKey == nullptr || UThematicUIButton::WidgetTheme == nullptr");
	}
}

void UThematicUIDropDownMenu::HandleOpening()
{
	if (USoundBase* SoundBase = Cast<USoundBase>(WidgetTheme->PressedTheme.Sound.GetResourceObject()))
		PlaySound(SoundBase);
}

void UThematicUIDropDownMenu::HandleSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (USoundBase* SoundBase = Cast<USoundBase>(WidgetTheme->PressedTheme.Sound.GetResourceObject()))
		PlaySound(SoundBase);
	OnSelectionChanged.Broadcast(ComboBoxString->GetSelectedOption(), ComboBoxString->GetSelectedIndex());
}
