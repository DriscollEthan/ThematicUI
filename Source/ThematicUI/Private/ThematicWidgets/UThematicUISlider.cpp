// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/UThematicUISlider.h"

#include "Components/SizeBox.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Slider.h"
#include "Kismet/GameplayStatics.h"

#include "Sound/SoundBase.h"

const FVector2D& UUThematicUISlider::GetSizeBoxSize() const
{
	return SizeBoxSize;
}

void UUThematicUISlider::SetSizeBoxSize(const FVector2D& NewSizeBoxSize)
{
	SizeBoxSize = NewSizeBoxSize;
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(SizeBoxSize.X);
		SizeBox->SetHeightOverride(SizeBoxSize.Y);
	}
}

const float UUThematicUISlider::GetCurrentValue() const
{
	return CurrentValue;
}

void UUThematicUISlider::SetCurrentValue(const float NewCurrentValue)
{
	if (Slider)
	{
		Slider->SetValue(GetPercentage());
	}
	if (ProgressBar)
	{
		ProgressBar->SetPercent(GetPercentage());
	}
	
	CurrentValue = NewCurrentValue;
}

FVector2D UUThematicUISlider::GetValueRange() const
{
	return ValueRange;
}

void UUThematicUISlider::SetValueRange(const FVector2D& NewValueRange)
{
	ValueRange = NewValueRange;
	
	float Percentage = GetPercentage();
	Percentage = (CurrentValue - ValueRange.X + StepAmount) / (ValueRange.Y - ValueRange.X) - Percentage;
	
	Slider->SetStepSize(Percentage);
	
	CurrentValue = CalculateCurrentValue(Slider->GetValue());
}

float UUThematicUISlider::GetStepAmount() const
{
	return StepAmount;
}

void UUThematicUISlider::SetStepAmount(const float NewStepAmount)
{
	StepAmount = NewStepAmount;
	
	float Percentage = GetPercentage();
	Percentage = (CurrentValue - ValueRange.X + StepAmount) / (ValueRange.Y - ValueRange.X) - Percentage;
	
	if (Slider)
	{
		Slider->SetStepSize(Percentage);
	}
}

const bool UUThematicUISlider::GetbIsHorizontal() const
{
	return bIsHorizontal;
}

void UUThematicUISlider::SetbIsHorizontal(const bool NewbIsHorizontal)
{
	bIsHorizontal = NewbIsHorizontal;
	
	if (ProgressBar)
	{
		EProgressBarFillType::Type BarFillType = (bIsHorizontal) ? EProgressBarFillType::Type::LeftToRight : EProgressBarFillType::Type::BottomToTop;
		ProgressBar->SetBarFillType(BarFillType);
	}
}

const FVector2D& UUThematicUISlider::GetThumbSize() const
{
	return ThumbSize;
}

void UUThematicUISlider::SetThumbSize(const FVector2D& NewThumbSize)
{
	ThumbSize = NewThumbSize;
}


const FText& UUThematicUISlider::GetText() const
{
	return Text;
}

void UUThematicUISlider::SetText(const FText& NewText)
{
	Text = NewText;
	
	if (Text.IsEmptyOrWhitespace() && !bAlwaysShowValue)
	{
		TextBlock->SetText(Text);
		return;
	}
	
#define LOCTEXT_NAMESPACE "Text"
	FText ActualText = Text;
	FText Delimiter = FText();
	if (!Text.IsEmptyOrWhitespace()) Delimiter = FText::FromString(":");
	FText Value = (bShowValueAsPercentage) ? FText::AsNumber(GetPercentage()) : FText::AsNumber(CurrentValue);
	FText Percentage = (bShowValueAsPercentage) ? FText::FromString("%") : FText();
	FFormatNamedArguments Args;
	Args.Add(TEXT("Text"), ActualText);
	Args.Add(TEXT("Delimiter"), Delimiter);
	Args.Add(TEXT("Float"), Value);
	Args.Add(TEXT("Percentage"), Percentage);
	ActualText = FText().Format(LOCTEXT("Text", "{Text}{Delimiter} {Float}{Percentage}"), Args);
	TextBlock->SetText(ActualText);
#undef LOCTEXT_NAMESPACE
}

const bool UUThematicUISlider::GetbAlwaysShowValue() const
{
	return bAlwaysShowValue;
}

void UUThematicUISlider::SetbAlwaysShowValue(const bool NewbAlwaysShowValue)
{
	bAlwaysShowValue = NewbAlwaysShowValue;
	
	SetText(Text);
}

const bool UUThematicUISlider::GetbShowValueAsPercentage() const
{
	return bShowValueAsPercentage;
}

void UUThematicUISlider::SetbShowValueAsPercentage(const bool NewbShowValueAsPercentage)
{
	bShowValueAsPercentage = NewbShowValueAsPercentage;
	SetText(Text);
}

const float UUThematicUISlider::GetPercentage() const
{
	return ((CurrentValue - ValueRange.X) / (ValueRange.Y - ValueRange.X));
}

const float UUThematicUISlider::CalculateCurrentValue(const float Percentage) const
{
	float Value = ValueRange.Y - ValueRange.X;
	Value *= Percentage;
	Value += ValueRange.X;
	Value = FMath::Clamp(Value, ValueRange.X, ValueRange.Y);
	return Value;
}

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
		Slider->SetValue(GetPercentage());
	}
	if (ProgressBar)
	{
		ProgressBar->SetPercent(GetPercentage());
		EProgressBarFillType::Type BarFillType = (bIsHorizontal) ? EProgressBarFillType::Type::LeftToRight : EProgressBarFillType::Type::BottomToTop;
		ProgressBar->SetBarFillType(BarFillType);
	}
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
		FSlateBrush BarBrush = ActualThemeData.NormalTheme.Image;
		BarBrush.DrawAs = ESlateBrushDrawType::NoDrawType;
		SliderStyle.SetNormalBarImage(BarBrush);
		SliderStyle.SetHoveredBarImage(BarBrush);
		
		// Setup Thumb Style
		FSlateBrush ThumbBrush = ActualThemeData.NormalTheme.Image;
		ThumbBrush.ImageSize = ThumbSize;
		ThumbBrush.OutlineSettings.CornerRadii = ActualThemeData.NormalTheme.Image.OutlineSettings.CornerRadii / 3;
		ThumbBrush.TintColor = ActualThemeData.NormalTheme.FillColor;
		SliderStyle.SetNormalThumbImage(ThumbBrush);
		SliderStyle.SetHoveredThumbImage(ThumbBrush);
		
		Slider->SetWidgetStyle(SliderStyle);
		
		// Set Progress Bar
		FProgressBarStyle BarStyle;
		
		// Set BackgroundImage
		BarStyle.SetBackgroundImage(ActualThemeData.NormalTheme.Image);
		
		// Set FillImage
		FSlateBrush FillBrush = ActualThemeData.NormalTheme.Image;
		FillBrush.TintColor = ActualThemeData.NormalTheme.FillColor;
		BarStyle.SetFillImage(FillBrush);
		
		ProgressBar->SetWidgetStyle(BarStyle);
		
		// Set TextBlock
		TextBlock->SetFont(ActualThemeData.NormalTheme.TextFont);
		TextBlock->SetColorAndOpacity(ActualThemeData.NormalTheme.TextColor);
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
		FSlateBrush BarBrush = ActualThemeData.HoveredTheme.Image;
		BarBrush.DrawAs = ESlateBrushDrawType::NoDrawType;
		SliderStyle.SetNormalBarImage(BarBrush);
		SliderStyle.SetHoveredBarImage(BarBrush);
		
		// Setup Thumb Style
		FSlateBrush ThumbBrush = ActualThemeData.HoveredTheme.Image;
		ThumbBrush.ImageSize = ThumbSize;
		ThumbBrush.OutlineSettings.CornerRadii = ActualThemeData.HoveredTheme.Image.OutlineSettings.CornerRadii / 3;
		ThumbBrush.TintColor = ActualThemeData.HoveredTheme.FillColor;
		SliderStyle.SetNormalThumbImage(ThumbBrush);
		SliderStyle.SetHoveredThumbImage(ThumbBrush);
		
		Slider->SetWidgetStyle(SliderStyle);
		
		// Set Progress Bar
		FProgressBarStyle BarStyle;
		
		// Set BackgroundImage
		BarStyle.SetBackgroundImage(ActualThemeData.HoveredTheme.Image);
		
		// Set FillImage
		FSlateBrush FillBrush = ActualThemeData.HoveredTheme.Image;
		FillBrush.TintColor = ActualThemeData.HoveredTheme.FillColor;
		BarStyle.SetFillImage(FillBrush);
		
		ProgressBar->SetWidgetStyle(BarStyle);

		// Set TextBlock
		TextBlock->SetFont(ActualThemeData.HoveredTheme.TextFont);
		TextBlock->SetColorAndOpacity(ActualThemeData.HoveredTheme.TextColor);
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
		FSlateBrush BarBrush = ActualThemeData.PressedTheme.Image;
		BarBrush.DrawAs = ESlateBrushDrawType::NoDrawType;
		SliderStyle.SetNormalBarImage(BarBrush);
		SliderStyle.SetHoveredBarImage(BarBrush);
		
		// Setup Thumb Style
		FSlateBrush ThumbBrush = ActualThemeData.PressedTheme.Image;
		ThumbBrush.ImageSize = ThumbSize;
		ThumbBrush.OutlineSettings.CornerRadii = ActualThemeData.PressedTheme.Image.OutlineSettings.CornerRadii / 3;
		ThumbBrush.TintColor = ActualThemeData.PressedTheme.FillColor;
		SliderStyle.SetNormalThumbImage(ThumbBrush);
		SliderStyle.SetHoveredThumbImage(ThumbBrush);
		
		Slider->SetWidgetStyle(SliderStyle);
		
		// Set Progress Bar
		FProgressBarStyle BarStyle;
		
		// Set BackgroundImage
		BarStyle.SetBackgroundImage(ActualThemeData.PressedTheme.Image);
		
		// Set FillImage
		FSlateBrush FillBrush = ActualThemeData.PressedTheme.Image;
		FillBrush.TintColor = ActualThemeData.PressedTheme.FillColor;
		BarStyle.SetFillImage(FillBrush);
		
		ProgressBar->SetWidgetStyle(BarStyle);
		
		// Set TextBlock
		TextBlock->SetFont(ActualThemeData.PressedTheme.TextFont);
		TextBlock->SetColorAndOpacity(ActualThemeData.PressedTheme.TextColor);
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

void UUThematicUISlider::HandleFloatValueChanged(const float NewValue)
{
	CurrentValue = CalculateCurrentValue(NewValue);
	ProgressBar->SetPercent(GetPercentage());
	SetText(Text);
	TUiOnValueChanged.Broadcast(CurrentValue);
}

void UUThematicUISlider::HandleControllerFocus()
{
	SetThemePressed();
	if (USoundBase* SoundBase = Cast<USoundBase>(ActualThemeData.PressedTheme.Sound.GetResourceObject()))
		PlaySound(SoundBase);
}

void UUThematicUISlider::HandleControllerUnFocused()
{
	if (Slider->HasAnyUserFocus())
		SetThemeHovered();
}
