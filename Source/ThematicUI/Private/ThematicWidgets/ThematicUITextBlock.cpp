// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/ThematicUITextBlock.h"

#include "Components/Border.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"

void UThematicUITextBlock::SetText(FText NewText)
{
	Text = NewText;
	
	TextBlock->SetText(Text);
}

void UThematicUITextBlock::NativePreConstruct()
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
		TextBlock->SetLineHeightPercentage(LineHeightPercentage);
		TextBlock->SetJustification(Justification);
	}
}

void UThematicUITextBlock::NativeConstruct()
{
	Super::NativeConstruct();
}

void UThematicUITextBlock::SetThemeNormal()
{
	Super::SetThemeNormal();
	
	if (Border && TextBlock && WidgetTheme)
	{
		Border->SetBrush(ActualThemeData.NormalTheme.Image);
		TextBlock->SetFont(ActualThemeData.NormalTheme.TextFont);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUITextBlock::SetThemeNormal : UThematicUITextBlock::Border == nullptr || UThematicUITextBlock::TextBlock == nullptr || UThematicUITextBlock::WidgetTheme == nullptr");
	}
}

void UThematicUITextBlock::SetThemeHovered()
{
	Super::SetThemeHovered();
	
	if (Border && TextBlock && WidgetTheme)
	{
		Border->SetBrush(ActualThemeData.NormalTheme.Image);
		TextBlock->SetFont(ActualThemeData.NormalTheme.TextFont);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUITextBlock::SetThemeHovered : UThematicUITextBlock::Border == nullptr || UThematicUITextBlock::TextBlock == nullptr || UThematicUITextBlock::WidgetTheme == nullptr");
	}
}

void UThematicUITextBlock::SetThemePressed()
{
	Super::SetThemePressed();
	
	if (Border && TextBlock && WidgetTheme)
	{
		Border->SetBrush(ActualThemeData.NormalTheme.Image);
		TextBlock->SetFont(ActualThemeData.NormalTheme.TextFont);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUITextBlock::SetThemePressed : UThematicUITextBlock::Border == nullptr || UThematicUITextBlock::TextBlock == nullptr || UThematicUITextBlock::WidgetTheme == nullptr");
	}
}
