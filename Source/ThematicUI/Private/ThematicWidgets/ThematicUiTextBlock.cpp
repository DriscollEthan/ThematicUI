// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/ThematicUiTextBlock.h"

#include "Components/Border.h"
#include "Components/TextBlock.h"

const FText& UThematicUiTextBlock::GetText() const
{
	return Text;
}

void UThematicUiTextBlock::SetText(const FText& NewText)
{
	Text = NewText;
	
	if (TextBlock)
	{
		TextBlock->SetText(Text);
	}
}

const float UThematicUiTextBlock::GetLineHeightPercentage() const
{
	return LineHeightPercentage;
}

void UThematicUiTextBlock::SetLineHeightPercentage(const float NewLineHeightPercentage)
{
	LineHeightPercentage = NewLineHeightPercentage;
	
	if (TextBlock)
	{
		TextBlock->SetLineHeightPercentage(LineHeightPercentage);
	}
}

const ETextJustify::Type UThematicUiTextBlock::GetJustification() const
{
	return Justification;
}

void UThematicUiTextBlock::SetJustification(const ETextJustify::Type& NewJustification)
{
	Justification = NewJustification;
	
	if (TextBlock)
	{
		TextBlock->SetJustification(Justification);
	}
}

void UThematicUiTextBlock::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (TextBlock)
	{
		TextBlock->SetText(Text);
		TextBlock->SetLineHeightPercentage(LineHeightPercentage);
		TextBlock->SetJustification(Justification);
	}
	
	
	// Turn off Sounds and then Recalculate the Theme Data.
	PrimaryWidgetData.WidgetThemeOverrideData.NormalThemeOverride.bOverrideSound = true;
	PrimaryWidgetData.WidgetThemeOverrideData.NormalThemeOverride.Sound = FSlateSound();
	
	PrimaryWidgetData.WidgetThemeOverrideData.HoveredThemeOverride.bOverrideSound = true;
	PrimaryWidgetData.WidgetThemeOverrideData.HoveredThemeOverride.Sound = FSlateSound();
	
	PrimaryWidgetData.WidgetThemeOverrideData.PressedThemeOverride.bOverrideSound = true;
	PrimaryWidgetData.WidgetThemeOverrideData.PressedThemeOverride.Sound = FSlateSound();
	
	CalculateAndSetActualWidgetThemeData();
}

void UThematicUiTextBlock::NativeConstruct()
{
	Super::NativeConstruct();
}

void UThematicUiTextBlock::SetThemeNormal()
{
	Super::SetThemeNormal();
	
	if (Border && TextBlock)
	{
		Border->SetBrush(ActualThemeData.NormalTheme.Image);
		TextBlock->SetFont(ActualThemeData.NormalTheme.TextFont);
		TextBlock->SetColorAndOpacity(ActualThemeData.NormalTheme.TextColor);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUiTextBlock::SetThemeNormal : UThematicUiTextBlock::Border == nullptr || UThematicUiTextBlock::TextBlock == nullptr");
	}
}

void UThematicUiTextBlock::SetThemeHovered()
{
	Super::SetThemeHovered();
	
	if (Border && TextBlock)
	{
		Border->SetBrush(ActualThemeData.NormalTheme.Image);
		TextBlock->SetFont(ActualThemeData.NormalTheme.TextFont);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUiTextBlock::SetThemeHovered : UThematicUiTextBlock::Border == nullptr || UThematicUiTextBlock::TextBlock == nullptr");
	}
}

void UThematicUiTextBlock::SetThemePressed()
{
	Super::SetThemePressed();
	
	if (Border && TextBlock)
	{
		Border->SetBrush(ActualThemeData.NormalTheme.Image);
		TextBlock->SetFont(ActualThemeData.NormalTheme.TextFont);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUiTextBlock::SetThemePressed : UThematicUiTextBlock::Border == nullptr || UThematicUiTextBlock::TextBlock == nullptr");
	}
}
