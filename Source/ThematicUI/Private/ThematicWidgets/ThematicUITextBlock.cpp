// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/ThematicUITextBlock.h"

#include "Components/Border.h"
#include "Components/TextBlock.h"

const FText& UThematicUITextBlock::GetText() const
{
	return Text;
}

void UThematicUITextBlock::SetText(const FText& NewText)
{
	Text = NewText;
	
	if (TextBlock)
	{
		TextBlock->SetText(Text);
	}
}

const float UThematicUITextBlock::GetLineHeightPercentage() const
{
	return LineHeightPercentage;
}

void UThematicUITextBlock::SetLineHeightPercentage(const float NewLineHeightPercentage)
{
	LineHeightPercentage = NewLineHeightPercentage;
	
	if (TextBlock)
	{
		TextBlock->SetLineHeightPercentage(LineHeightPercentage);
	}
}

const ETextJustify::Type UThematicUITextBlock::GetJustification() const
{
	return Justification;
}

void UThematicUITextBlock::SetJustification(const ETextJustify::Type& NewJustification)
{
	Justification = NewJustification;
	
	if (TextBlock)
	{
		TextBlock->SetJustification(Justification);
	}
}

void UThematicUITextBlock::NativePreConstruct()
{
	Super::NativePreConstruct();
	
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
	
	if (Border && TextBlock)
	{
		Border->SetBrush(ActualThemeData.NormalTheme.Image);
		TextBlock->SetFont(ActualThemeData.NormalTheme.TextFont);
		TextBlock->SetColorAndOpacity(ActualThemeData.NormalTheme.TextColor);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUITextBlock::SetThemeNormal : UThematicUITextBlock::Border == nullptr || UThematicUITextBlock::TextBlock == nullptr");
	}
}

void UThematicUITextBlock::SetThemeHovered()
{
	Super::SetThemeHovered();
	
	if (Border && TextBlock)
	{
		Border->SetBrush(ActualThemeData.NormalTheme.Image);
		TextBlock->SetFont(ActualThemeData.NormalTheme.TextFont);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUITextBlock::SetThemeHovered : UThematicUITextBlock::Border == nullptr || UThematicUITextBlock::TextBlock == nullptr");
	}
}

void UThematicUITextBlock::SetThemePressed()
{
	Super::SetThemePressed();
	
	if (Border && TextBlock)
	{
		Border->SetBrush(ActualThemeData.NormalTheme.Image);
		TextBlock->SetFont(ActualThemeData.NormalTheme.TextFont);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUITextBlock::SetThemePressed : UThematicUITextBlock::Border == nullptr || UThematicUITextBlock::TextBlock == nullptr");
	}
}
