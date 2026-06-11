// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/ThematicUIDropDownMenu.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/ComboBoxString.h"
#include "Components/OverlaySlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "Sound/SoundBase.h"


void UThematicUIDropDownMenu::SetDropDownArrowBrush(const FSlateBrush& NewDropDownArrowBrush)
{
	DropDownArrowBrush = NewDropDownArrowBrush;
	
	if (DropDownArrowImage)
	{
		DropDownArrowImage->SetBrush(DropDownArrowBrush);
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

void UThematicUIDropDownMenu::SetSelectedIndex(const int NewSelectedIndex)
{
	ComboBoxString->SetSelectedIndex(NewSelectedIndex);
	
	HandleSelectionChanged(ComboBoxString->GetSelectedOption(), ESelectInfo::Type::Direct);
}

const FString UThematicUIDropDownMenu::GetSelectedOption() const
{
	return ComboBoxString->GetSelectedOption();
}

const int UThematicUIDropDownMenu::GetSelectedIndex() const
{
	return  ComboBoxString->GetSelectedIndex();
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
	if (SelectedOptionTextBlock)
	{
		SelectedOptionTextBlock->SetText(FText::FromString(SelectedItem));
	}
}

void UThematicUIDropDownMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
	
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
	
	if (SelectedOptionTextBlock)
	{
		if (UOverlaySlot* OverlaySlot = UWidgetLayoutLibrary::SlotAsOverlaySlot(SelectedOptionTextBlock))
		{
			OverlaySlot->SetHorizontalAlignment(HAlign_Left);
			OverlaySlot->SetVerticalAlignment(VAlign_Center);
			OverlaySlot->SetPadding(FMargin(4.0f, 0.0f, 0.0f, 0.0f));
		}
		SelectedOptionTextBlock->SetText(FText::FromString(ComboBoxString->GetSelectedOption()));
	}
}

void UThematicUIDropDownMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (ComboBoxString)
	{
		ComboBoxString->OnOpening.AddUniqueDynamic(this, &UThematicUIDropDownMenu::UThematicUIDropDownMenu::HandleOpening);
		ComboBoxString->OnSelectionChanged.AddUniqueDynamic(this, &UThematicUIDropDownMenu::HandleSelectionChanged);
	}
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
	
	if (ComboBoxString && SelectedOptionTextBlock && DropDownArrowImage)
	{
		SelectedOptionTextBlock->SetColorAndOpacity(ActualThemeData.NormalTheme.TextColor);
		SelectedOptionTextBlock->SetFont(ActualThemeData.NormalTheme.TextFont);
		
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
		
		DropDownArrowImage->SetBrush(DropDownArrowBrush);
		ComboBoxString->SetWidgetStyle(DropDownStyle);
		ComboBoxString->SetItemStyle(DropDownRowStyle);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUIDropDownMenu::SetThemeNormal : UThematicUIDropDownMenu::ComboBoxKey == nullptr || UThematicUIDropDownMenu::DropDownArrowImage == nullptr || UThematicUIDropDownMenu::Border == nullptr");
	}
}

void UThematicUIDropDownMenu::SetThemeHovered()
{
	Super::SetThemeHovered();
	
	if (ComboBoxString && SelectedOptionTextBlock)
	{
		SelectedOptionTextBlock->SetColorAndOpacity(ActualThemeData.HoveredTheme.TextColor);
		SelectedOptionTextBlock->SetFont(ActualThemeData.HoveredTheme.TextFont);

		
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
		
		DropDownArrowImage->SetBrush(DropDownArrowBrush);
		ComboBoxString->SetWidgetStyle(DropDownStyle);
		ComboBoxString->SetItemStyle(DropDownRowStyle);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUIDropDownMenu::SetThemeHovered : UThematicUIDropDownMenu::ComboBoxKey == nullptr || UThematicUIDropDownMenu::DropDownArrowImage == nullptr || UThematicUIDropDownMenu::Border == nullptr");
	}
}

void UThematicUIDropDownMenu::SetThemePressed()
{
	Super::SetThemePressed();
	
	if (ComboBoxString && SelectedOptionTextBlock)
	{
		SelectedOptionTextBlock->SetColorAndOpacity(ActualThemeData.PressedTheme.TextColor);
		SelectedOptionTextBlock->SetFont(ActualThemeData.PressedTheme.TextFont);

		
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
		
		DropDownArrowImage->SetBrush(DropDownArrowBrush);
		ComboBoxString->SetWidgetStyle(DropDownStyle);
		ComboBoxString->SetItemStyle(DropDownRowStyle);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUIDropDownMenu::SetThemePressed : UThematicUIDropDownMenu::ComboBoxKey == nullptr || UThematicUIDropDownMenu::DropDownArrowImage == nullptr || UThematicUIDropDownMenu::Border == nullptr");
	}
}