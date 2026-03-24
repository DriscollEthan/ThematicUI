// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/ThematicUIDropDownMenu.h"

#include "Components/ComboBoxString.h"
#include "Components/SizeBox.h"

#include "Sound/SoundBase.h"

const FVector2D& UThematicUIDropDownMenu::GetSizeBoxSize() const
{
	return SizeBoxSize;
}

void UThematicUIDropDownMenu::SetSizeBoxSize(const FVector2D& NewSizeBoxSize)
{
	SizeBoxSize = NewSizeBoxSize;
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(SizeBoxSize.X);
		SizeBox->SetHeightOverride(SizeBoxSize.Y);
	}
}

const TArray<FString>& UThematicUIDropDownMenu::GetOptions() const
{
	return Options;
}

void UThematicUIDropDownMenu::SetOptions(const TArray<FString>& NewOptions)
{
	Options = NewOptions;
	
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
}

void UThematicUIDropDownMenu::HandleOpening()
{
	if (USoundBase* SoundBase = Cast<USoundBase>(ActualThemeData.PressedTheme.Sound.GetResourceObject()))
		PlaySound(SoundBase);
}

void UThematicUIDropDownMenu::HandleSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (USoundBase* SoundBase = Cast<USoundBase>(ActualThemeData.PressedTheme.Sound.GetResourceObject()))
		PlaySound(SoundBase);
	OnSelectionChanged.Broadcast(ComboBoxString->GetSelectedOption(), ComboBoxString->GetSelectedIndex());
}

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
		FSlateBrush ItemStyleNormalImage = ActualThemeData.NormalTheme.Image;
		ItemStyleNormalImage.OutlineSettings.Width = -100.0f;
		ItemStyleNormalImage.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
		FSlateBrush ItemStyleHoveredImage = ActualThemeData.HoveredTheme.Image;
		ItemStyleHoveredImage.OutlineSettings.Width = -100.0f;
		ItemStyleHoveredImage.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
		FSlateBrush ItemStylePressedImage = ActualThemeData.PressedTheme.Image;
		ItemStylePressedImage.OutlineSettings.Width = -100.0f;
		ItemStylePressedImage.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
		
		DropDownStyle.ComboButtonStyle.ButtonStyle.Normal = ActualThemeData.NormalTheme.Image;
		DropDownStyle.ComboButtonStyle.ButtonStyle.Hovered = ActualThemeData.NormalTheme.Image;
		DropDownStyle.ComboButtonStyle.ButtonStyle.Pressed = ActualThemeData.NormalTheme.Image;
		DropDownStyle.ComboButtonStyle.DownArrowImage = DropDownArrowBrush;
		DropDownStyle.ComboButtonStyle.DownArrowImage.TintColor = ActualThemeData.NormalTheme.Image.OutlineSettings.Color;
		
		DropDownRowStyle.SelectorFocusedBrush.TintColor.GetSpecifiedColor() = ActualThemeData.NormalTheme.FillColor;
		DropDownRowStyle.EvenRowBackgroundBrush = ItemStyleNormalImage;
		DropDownRowStyle.OddRowBackgroundBrush = ItemStyleNormalImage;
		DropDownRowStyle.EvenRowBackgroundHoveredBrush = ItemStyleHoveredImage;
		DropDownRowStyle.OddRowBackgroundHoveredBrush = ItemStyleHoveredImage;
		DropDownRowStyle.TextColor = ActualThemeData.NormalTheme.TextColor;
		DropDownRowStyle.SelectedTextColor = ActualThemeData.PressedTheme.TextColor;
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
		FSlateBrush ItemStyleNormalImage = ActualThemeData.NormalTheme.Image;
		ItemStyleNormalImage.OutlineSettings.Width = -100.0f;
		ItemStyleNormalImage.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
		FSlateBrush ItemStyleHoveredImage = ActualThemeData.HoveredTheme.Image;
		ItemStyleHoveredImage.OutlineSettings.Width = -100.0f;
		ItemStyleHoveredImage.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
		FSlateBrush ItemStylePressedImage = ActualThemeData.PressedTheme.Image;
		ItemStylePressedImage.OutlineSettings.Width = -100.0f;
		ItemStylePressedImage.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
		
		DropDownStyle.ComboButtonStyle.ButtonStyle.Normal = ActualThemeData.HoveredTheme.Image;
		DropDownStyle.ComboButtonStyle.ButtonStyle.Hovered = ActualThemeData.HoveredTheme.Image;
		DropDownStyle.ComboButtonStyle.ButtonStyle.Pressed = ActualThemeData.HoveredTheme.Image;
		DropDownStyle.ComboButtonStyle.DownArrowImage = DropDownArrowBrush;
		DropDownStyle.ComboButtonStyle.DownArrowImage.TintColor = ActualThemeData.HoveredTheme.Image.OutlineSettings.Color;
		
		DropDownRowStyle.SelectorFocusedBrush.TintColor.GetSpecifiedColor() = ActualThemeData.NormalTheme.FillColor;
		DropDownRowStyle.EvenRowBackgroundBrush = ItemStyleNormalImage;
		DropDownRowStyle.OddRowBackgroundBrush = ItemStyleNormalImage;
		DropDownRowStyle.EvenRowBackgroundHoveredBrush = ItemStyleHoveredImage;
		DropDownRowStyle.OddRowBackgroundHoveredBrush = ItemStyleHoveredImage;
		DropDownRowStyle.TextColor = ActualThemeData.NormalTheme.TextColor;
		DropDownRowStyle.SelectedTextColor = ActualThemeData.PressedTheme.TextColor;
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
		FSlateBrush ItemStyleNormalImage = ActualThemeData.NormalTheme.Image;
		ItemStyleNormalImage.OutlineSettings.Width = -100.0f;
		ItemStyleNormalImage.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
		FSlateBrush ItemStyleHoveredImage = ActualThemeData.HoveredTheme.Image;
		ItemStyleHoveredImage.OutlineSettings.Width = -100.0f;
		ItemStyleHoveredImage.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
		FSlateBrush ItemStylePressedImage = ActualThemeData.PressedTheme.Image;
		ItemStylePressedImage.OutlineSettings.Width = -100.0f;
		ItemStylePressedImage.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
		
		DropDownStyle.ComboButtonStyle.ButtonStyle.Normal = ActualThemeData.PressedTheme.Image;
		DropDownStyle.ComboButtonStyle.ButtonStyle.Hovered = ActualThemeData.PressedTheme.Image;
		DropDownStyle.ComboButtonStyle.ButtonStyle.Pressed = ActualThemeData.PressedTheme.Image;
		DropDownStyle.ComboButtonStyle.DownArrowImage = DropDownArrowBrush;
		DropDownStyle.ComboButtonStyle.DownArrowImage.TintColor = ActualThemeData.PressedTheme.Image.OutlineSettings.Color;
		
		DropDownRowStyle.SelectorFocusedBrush.TintColor.GetSpecifiedColor() = ActualThemeData.NormalTheme.FillColor;
		DropDownRowStyle.EvenRowBackgroundBrush = ItemStyleNormalImage;
		DropDownRowStyle.OddRowBackgroundBrush = ItemStyleNormalImage;
		DropDownRowStyle.EvenRowBackgroundHoveredBrush = ItemStyleHoveredImage;
		DropDownRowStyle.OddRowBackgroundHoveredBrush = ItemStyleHoveredImage;
		DropDownRowStyle.TextColor = ActualThemeData.NormalTheme.TextColor;
		DropDownRowStyle.SelectedTextColor = ActualThemeData.PressedTheme.TextColor;
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