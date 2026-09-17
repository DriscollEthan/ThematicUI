// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/UThematicUiSlider.h"

#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Slider.h"
#include "Kismet/GameplayStatics.h"

#include "Sound/SoundBase.h"

const float UUThematicUiSlider::GetCurrentValue() const
{
	return CurrentValue;
}

void UUThematicUiSlider::SetCurrentValue(const float NewCurrentValue)
{
	CurrentValue = NewCurrentValue;

	if (Slider)
	{
		Slider->SetValue(GetPercentage());
	}
	if (ProgressBar)
	{
		ProgressBar->SetPercent(GetPercentage());
	}
}

FVector2D UUThematicUiSlider::GetValueRange() const
{
	return ValueRange;
}

void UUThematicUiSlider::SetValueRange(const FVector2D& NewValueRange)
{
	ValueRange = NewValueRange;
	
	float Percentage = GetPercentage();
	Percentage = (CurrentValue - ValueRange.X + StepAmount) / (ValueRange.Y - ValueRange.X) - Percentage;
	
	Slider->SetStepSize(Percentage);
	
	CurrentValue = CalculateCurrentValue(Slider->GetValue());
}

float UUThematicUiSlider::GetStepAmount() const
{
	return StepAmount;
}

void UUThematicUiSlider::SetStepAmount(const float NewStepAmount)
{
	StepAmount = NewStepAmount;
	
	float Percentage = GetPercentage();
	Percentage = (CurrentValue - ValueRange.X + StepAmount) / (ValueRange.Y - ValueRange.X) - Percentage;
	
	if (Slider)
	{
		Slider->SetStepSize(Percentage);
	}
}

const bool UUThematicUiSlider::GetbIsHorizontal() const
{
	return bIsHorizontal;
}

void UUThematicUiSlider::SetbIsHorizontal(const bool NewbIsHorizontal)
{
	bIsHorizontal = NewbIsHorizontal;
	
	if (ProgressBar)
	{
		EProgressBarFillType::Type BarFillType = (bIsHorizontal) ? EProgressBarFillType::Type::LeftToRight : EProgressBarFillType::Type::BottomToTop;
		ProgressBar->SetBarFillType(BarFillType);
	}
}

const FVector2D& UUThematicUiSlider::GetThumbSize() const
{
	return ThumbSize;
}

void UUThematicUiSlider::SetThumbSize(const FVector2D& NewThumbSize)
{
	ThumbSize = NewThumbSize;
}


const FText& UUThematicUiSlider::GetText() const
{
	return Text;
}

void UUThematicUiSlider::SetText(const FText& NewText)
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
	FText Value = (bShowValueAsPercentage) ? FText::AsNumber(GetPercentage() * 100.0f) : FText::AsNumber(CurrentValue);
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

const bool UUThematicUiSlider::GetbAlwaysShowValue() const
{
	return bAlwaysShowValue;
}

void UUThematicUiSlider::SetbAlwaysShowValue(const bool NewbAlwaysShowValue)
{
	bAlwaysShowValue = NewbAlwaysShowValue;
	
	SetText(Text);
}

const bool UUThematicUiSlider::GetbShowValueAsPercentage() const
{
	return bShowValueAsPercentage;
}

void UUThematicUiSlider::SetbShowValueAsPercentage(const bool NewbShowValueAsPercentage)
{
	bShowValueAsPercentage = NewbShowValueAsPercentage;
	SetText(Text);
}

const float UUThematicUiSlider::GetPercentage() const
{
	return ((CurrentValue - ValueRange.X) / (ValueRange.Y - ValueRange.X));
}

const float UUThematicUiSlider::CalculateCurrentValue(const float Percentage) const
{
	float Value = ValueRange.Y - ValueRange.X;
	Value *= Percentage;
	Value += ValueRange.X;
	Value = FMath::Clamp(Value, ValueRange.X, ValueRange.Y);
	return Value;
}

void UUThematicUiSlider::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	CurrentValue = CalculateCurrentValue(GetPercentage());
	
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

void UUThematicUiSlider::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (Slider)
	{
		Slider->OnValueChanged.AddUniqueDynamic(this, &UUThematicUiSlider::HandleFloatValueChanged);
		Slider->OnControllerCaptureBegin.AddUniqueDynamic(this, &UUThematicUiSlider::HandleControllerFocus);
		Slider->OnControllerCaptureEnd.AddUniqueDynamic(this, &UUThematicUiSlider::HandleControllerUnFocused);
	}
	SetStepAmount(StepAmount);
}

void UUThematicUiSlider::SetThemeNormal()
{
	Super::SetThemeNormal();
	
	if (Slider && ProgressBar && TextBlock)
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
		UE_LOGFMT(LogThematicUI, Error, "UUThematicUiSlider::SetThemeNormal : UUThematicUiSlider::Slider == nullptr || UUThematicUiSlider::ProgressBar == nullptr || UUThematicUiSlider::TextBlock == nullptr");
	}
}

void UUThematicUiSlider::SetThemeHovered()
{
	Super::SetThemeHovered();
	
	if (Slider && ProgressBar && TextBlock)
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
		UE_LOGFMT(LogThematicUI, Error, "UUThematicUiSlider::SetThemeHovered : UUThematicUiSlider::Slider == nullptr || UUThematicUiSlider::ProgressBar == nullptr || UUThematicUiSlider::TextBlock == nullptr");
	}
}

void UUThematicUiSlider::SetThemePressed()
{
	Super::SetThemePressed();
	
	if (Slider && ProgressBar && TextBlock)
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
		UE_LOGFMT(LogThematicUI, Error, "UUThematicUiSlider::SetThemePressed : UUThematicUiSlider::Slider == nullptr || UUThematicUiSlider::ProgressBar == nullptr || UUThematicUiSlider::TextBlock == nullptr");
	}
}

FReply UUThematicUiSlider::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	if (Slider)
	{
		return FReply::Handled().SetUserFocus(Slider->TakeWidget(), InFocusEvent.GetCause());
	}
	
	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

void UUThematicUiSlider::HandleFloatValueChanged(const float NewValue)
{
	CurrentValue = CalculateCurrentValue(NewValue);
	ProgressBar->SetPercent(GetPercentage());
	SetText(Text);
	TUiOnValueChanged.Broadcast(CurrentValue);
}

void UUThematicUiSlider::HandleControllerFocus()
{
	SetThemePressed();
	if (USoundBase* SoundBase = Cast<USoundBase>(ActualThemeData.PressedTheme.Sound.GetResourceObject()))
		PlaySound(SoundBase);
}

void UUThematicUiSlider::HandleControllerUnFocused()
{
	if (Slider->HasAnyUserFocus())
		SetThemeHovered();
}
