// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/UThematicUISlider.h"

#include "Components/SizeBox.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Slider.h"

void UUThematicUISlider::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	CurrentValue = CalculateCurrentValue(GetPercentage());
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(SizeBoxSize.X);
		SizeBox->SetHeightOverride(SizeBoxSize.Y);
	}
	if (TextBlock)
	{
		SetText(Text);
	}
	if (Slider)
	{
		Slider->SetValue(CurrentValue);
	}
	if (ProgressBar)
	{
		ProgressBar->SetPercent(CurrentValue);
		EProgressBarFillType::Type BarFillType = (bIsHorizontal) ? EProgressBarFillType::Type::LeftToRight : EProgressBarFillType::Type::BottomToTop;
		ProgressBar->SetBarFillType(BarFillType);
	}
	
	SetThemeNormal();
}

void UUThematicUISlider::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (Slider)
	{
		Slider->OnValueChanged.AddUniqueDynamic(this, &UUThematicUISlider::HandleFloatValueChanged);
	}
	SetStepAmount(StepAmount);
}

void UUThematicUISlider::SetThemeNormal()
{
	Super::SetThemeNormal();
	
	if (Slider && ProgressBar && Border && TextBlock && WidgetTheme)
	{
		// Set Slider
		FSliderStyle SliderStyle;
		
		// Setup Bar Style
		FSlateBrush BarBrush = WidgetTheme->NormalTheme.Image;
		BarBrush.DrawAs = ESlateBrushDrawType::NoDrawType;
		SliderStyle.SetNormalBarImage(BarBrush);
		SliderStyle.SetHoveredBarImage(BarBrush);
		
		// Setup Thumb Style
		FSlateBrush ThumbBrush = WidgetTheme->NormalTheme.Image;
		ThumbBrush.ImageSize = ThumbSize;
		ThumbBrush.OutlineSettings.CornerRadii = WidgetTheme->NormalTheme.Image.OutlineSettings.CornerRadii / 3;
		ThumbBrush.TintColor = WidgetTheme->NormalTheme.FillColor;
		SliderStyle.SetNormalThumbImage(ThumbBrush);
		SliderStyle.SetHoveredThumbImage(ThumbBrush);
		
		Slider->SetWidgetStyle(SliderStyle);
		
		// Set Progress Bar
		FProgressBarStyle BarStyle;
		
		// Set BackgroundImage
		BarStyle.SetBackgroundImage(WidgetTheme->NormalTheme.Image);
		
		// Set FillImage
		FSlateBrush FillBrush = WidgetTheme->NormalTheme.Image;
		FillBrush.TintColor = WidgetTheme->NormalTheme.FillColor;
		BarStyle.SetFillImage(FillBrush);
		
		ProgressBar->SetWidgetStyle(BarStyle);
		
		// Set Border
		Border->SetBrush(WidgetTheme->NormalTheme.Image);
		
		// Set TextBlock
		TextBlock->SetFont(WidgetTheme->NormalTheme.TextFont);
		TextBlock->SetColorAndOpacity(WidgetTheme->NormalTheme.TextColor);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UUThematicUISlider::SetThemeNormal : UUThematicUISlider::Slider == nullptr || UUThematicUISlider::ProgressBar == nullptr || UUThematicUISlider::Border || UUThematicUISlider::TextBlock == nullptr || UUThematicUISlider::WidgetTheme == nullptr");
	}
}

void UUThematicUISlider::SetThemeHovered()
{
	Super::SetThemeHovered();
	
	if (Slider && ProgressBar && Border && TextBlock && WidgetTheme)
	{
		// Set Slider
		FSliderStyle SliderStyle;
		
		// Setup Bar Style
		FSlateBrush BarBrush = WidgetTheme->HoveredTheme.Image;
		BarBrush.DrawAs = ESlateBrushDrawType::NoDrawType;
		SliderStyle.SetNormalBarImage(BarBrush);
		SliderStyle.SetHoveredBarImage(BarBrush);
		
		// Setup Thumb Style
		FSlateBrush ThumbBrush = WidgetTheme->HoveredTheme.Image;
		ThumbBrush.ImageSize = ThumbSize;
		ThumbBrush.OutlineSettings.CornerRadii = WidgetTheme->HoveredTheme.Image.OutlineSettings.CornerRadii / 3;
		ThumbBrush.TintColor = WidgetTheme->HoveredTheme.FillColor;
		SliderStyle.SetNormalThumbImage(ThumbBrush);
		SliderStyle.SetHoveredThumbImage(ThumbBrush);
		
		Slider->SetWidgetStyle(SliderStyle);
		
		// Set Progress Bar
		FProgressBarStyle BarStyle;
		
		// Set BackgroundImage
		BarStyle.SetBackgroundImage(WidgetTheme->HoveredTheme.Image);
		
		// Set FillImage
		FSlateBrush FillBrush = WidgetTheme->HoveredTheme.Image;
		FillBrush.TintColor = WidgetTheme->HoveredTheme.FillColor;
		BarStyle.SetFillImage(FillBrush);
		
		ProgressBar->SetWidgetStyle(BarStyle);
		
		// Set Border
		Border->SetBrush(WidgetTheme->HoveredTheme.Image);
		
		// Set TextBlock
		TextBlock->SetFont(WidgetTheme->HoveredTheme.TextFont);
		TextBlock->SetColorAndOpacity(WidgetTheme->HoveredTheme.TextColor);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UUThematicUISlider::SetThemeHovered : UUThematicUISlider::Slider == nullptr || UUThematicUISlider::ProgressBar == nullptr || UUThematicUISlider::Border || UUThematicUISlider::TextBlock == nullptr || UUThematicUISlider::WidgetTheme == nullptr");
	}
}

FVector2D UUThematicUISlider::GetValueRange() const
{
	return ValueRange;
}

FVector2D UUThematicUISlider::GetThumbSize() const
{
	return ThumbSize;
}

void UUThematicUISlider::SetValueRange(const FVector2D& NewValueRange)
{
	ValueRange = NewValueRange;
	
	Slider->SetStepSize(UpdateSteppingSize());
	
	CurrentValue = CalculateCurrentValue(Slider->GetValue());
}

void UUThematicUISlider::SetThumbSize(const FVector2D& NewThumbSize)
{
	ThumbSize = NewThumbSize;
}

void UUThematicUISlider::SetText(const FText& NewText)
{
#define LOCTEXT_NAMESPACE "Text"
	FText ActualText = Text;
	FFormatNamedArguments Args;
	Args.Add(TEXT("Text"), ActualText);
	Args.Add(TEXT("Float"), FText::AsNumber(CurrentValue));
	ActualText = FText().Format(LOCTEXT("Text", "{Text}: {Float}"), Args);
	TextBlock->SetText(ActualText);
#undef LOCTEXT_NAMESPACE
}

FText UUThematicUISlider::GetText() const
{
	return Text;
}

float UUThematicUISlider::GetCurrentValue() const
{
	return CurrentValue;
}

float UUThematicUISlider::GetStepAmount() const
{
	return StepAmount;
}

float UUThematicUISlider::GetPercentage() const
{
	return ((CurrentValue - ValueRange.X) / (ValueRange.Y - ValueRange.X));
}

void UUThematicUISlider::SetStepAmount(const float NewStepAmount)
{
	StepAmount = NewStepAmount;
	
	if (Slider)
	{
		Slider->SetStepSize(UpdateSteppingSize());
	}
}

float UUThematicUISlider::CalculateCurrentValue(const float Percentage) const
{
	float Value = ValueRange.Y - ValueRange.X;
	Value *= Percentage;
	Value += ValueRange.X;
	return Value;
}

float UUThematicUISlider::UpdateSteppingSize() const
{
	float Percentage = GetPercentage();
	Percentage = (CurrentValue - ValueRange.X + StepAmount) / (ValueRange.Y - ValueRange.X) - Percentage;
	return Percentage;
}

void UUThematicUISlider::HandleFloatValueChanged(const float NewValue)
{
	CurrentValue = CalculateCurrentValue(NewValue);
	ProgressBar->SetPercent(NewValue);
	TUiOnValueChanged.Broadcast();
}
