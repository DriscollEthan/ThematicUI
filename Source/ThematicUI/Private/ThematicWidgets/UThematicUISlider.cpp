// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/UThematicUISlider.h"

#include "Components/SizeBox.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Slider.h"
#include "Kismet/GameplayStatics.h"

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
		Slider->OnControllerCaptureBegin.AddUniqueDynamic(this, &UUThematicUISlider::HandleControllerFocus);
		Slider->OnControllerCaptureEnd.AddUniqueDynamic(this, &UUThematicUISlider::HandleControllerUnFocused);
	}
	SetStepAmount(StepAmount);
}

void UUThematicUISlider::SetThemeNormal()
{
	Super::SetThemeNormal();
	
	if (Slider && ProgressBar && TextBlock && WidgetTheme)
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
		
		// Set TextBlock
		TextBlock->SetFont(WidgetTheme->NormalTheme.TextFont);
		TextBlock->SetColorAndOpacity(WidgetTheme->NormalTheme.TextColor);
		if (Text.IsEmptyOrWhitespace() && !bAlwaysShowValue)
		{
			TextBlock->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			TextBlock->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UUThematicUISlider::SetThemeNormal : UUThematicUISlider::Slider == nullptr || UUThematicUISlider::ProgressBar == nullptr || UUThematicUISlider::TextBlock == nullptr || UUThematicUISlider::WidgetTheme == nullptr");
	}
}

void UUThematicUISlider::SetThemeHovered()
{
	Super::SetThemeHovered();
	
	if (Slider && ProgressBar && TextBlock && WidgetTheme)
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

		// Set TextBlock
		TextBlock->SetFont(WidgetTheme->HoveredTheme.TextFont);
		TextBlock->SetColorAndOpacity(WidgetTheme->HoveredTheme.TextColor);
		if (Text.IsEmptyOrWhitespace() && !bAlwaysShowValue)
		{
			TextBlock->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			TextBlock->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UUThematicUISlider::SetThemeHovered : UUThematicUISlider::Slider == nullptr || UUThematicUISlider::ProgressBar == nullptr || UUThematicUISlider::TextBlock == nullptr || UUThematicUISlider::WidgetTheme == nullptr");
	}
}

void UUThematicUISlider::SetThemePressed()
{
	Super::SetThemePressed();
	
	if (Slider && ProgressBar && TextBlock && WidgetTheme)
	{
		// Set Slider
		FSliderStyle SliderStyle;
		
		// Setup Bar Style
		FSlateBrush BarBrush = WidgetTheme->PressedTheme.Image;
		BarBrush.DrawAs = ESlateBrushDrawType::NoDrawType;
		SliderStyle.SetNormalBarImage(BarBrush);
		SliderStyle.SetHoveredBarImage(BarBrush);
		
		// Setup Thumb Style
		FSlateBrush ThumbBrush = WidgetTheme->PressedTheme.Image;
		ThumbBrush.ImageSize = ThumbSize;
		ThumbBrush.OutlineSettings.CornerRadii = WidgetTheme->PressedTheme.Image.OutlineSettings.CornerRadii / 3;
		ThumbBrush.TintColor = WidgetTheme->PressedTheme.FillColor;
		SliderStyle.SetNormalThumbImage(ThumbBrush);
		SliderStyle.SetHoveredThumbImage(ThumbBrush);
		
		Slider->SetWidgetStyle(SliderStyle);
		
		// Set Progress Bar
		FProgressBarStyle BarStyle;
		
		// Set BackgroundImage
		BarStyle.SetBackgroundImage(WidgetTheme->PressedTheme.Image);
		
		// Set FillImage
		FSlateBrush FillBrush = WidgetTheme->PressedTheme.Image;
		FillBrush.TintColor = WidgetTheme->PressedTheme.FillColor;
		BarStyle.SetFillImage(FillBrush);
		
		ProgressBar->SetWidgetStyle(BarStyle);
		
		// Set TextBlock
		TextBlock->SetFont(WidgetTheme->PressedTheme.TextFont);
		TextBlock->SetColorAndOpacity(WidgetTheme->PressedTheme.TextColor);
		if (Text.IsEmptyOrWhitespace() && !bAlwaysShowValue)
		{
			TextBlock->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			TextBlock->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UUThematicUISlider::SetThemePressed : UUThematicUISlider::Slider == nullptr || UUThematicUISlider::ProgressBar == nullptr || UUThematicUISlider::TextBlock == nullptr || UUThematicUISlider::WidgetTheme == nullptr");
	}
}

FReply UUThematicUISlider::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	if (Slider)
	{
		return FReply::Handled().SetUserFocus(Slider->TakeWidget(), InFocusEvent.GetCause());
	}
	
	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

USlider* UUThematicUISlider::GetSliderRef()
{
	return Slider;
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
	if (NewText.IsEmptyOrWhitespace() && !bAlwaysShowValue)
	{
		TextBlock->SetText(NewText);
		return;
	}
	
#define LOCTEXT_NAMESPACE "Text"
	FText ActualText = NewText;
	FText Delimiter = FText();
	if (!NewText.IsEmptyOrWhitespace()) Delimiter = FText::FromString(":");
	FFormatNamedArguments Args;
	Args.Add(TEXT("Text"), ActualText);
	Args.Add(TEXT("Delimiter"), Delimiter);
	Args.Add(TEXT("Float"), FText::AsNumber(CurrentValue));
	ActualText = FText().Format(LOCTEXT("Text", "{Text}{Delimiter} {Float}"), Args);
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

void UUThematicUISlider::HandleControllerFocus()
{
	SetThemePressed();
}

void UUThematicUISlider::HandleControllerUnFocused()
{
	if (Slider->HasAnyUserFocus())
		SetThemeHovered();
}
