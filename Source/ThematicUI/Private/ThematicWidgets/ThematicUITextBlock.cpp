// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/ThematicUITextBlock.h"

#include "Components/Border.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"

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
	}
	
	SetThemeNormal();																																		
}

void UThematicUITextBlock::NativeConstruct()
{
	Super::NativeConstruct();
	
	SetThemeNormal();
}

void UThematicUITextBlock::SetThemeNormal()
{
	Super::SetThemeNormal();
	
	if (Border && TextBlock && WidgetTheme)
	{
		Border->SetBrush(WidgetTheme->NormalTheme.Image);
		TextBlock->SetFont(WidgetTheme->NormalTheme.TextFont);
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
		Border->SetBrush(WidgetTheme->NormalTheme.Image);
		TextBlock->SetFont(WidgetTheme->NormalTheme.TextFont);
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
		Border->SetBrush(WidgetTheme->NormalTheme.Image);
		TextBlock->SetFont(WidgetTheme->NormalTheme.TextFont);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUITextBlock::SetThemePressed : UThematicUITextBlock::Border == nullptr || UThematicUITextBlock::TextBlock == nullptr || UThematicUITextBlock::WidgetTheme == nullptr");
	}
}
