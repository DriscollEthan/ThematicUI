// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/UThematicUIRadialSlider.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"
#include "Components/RadialSlider.h"
#include "Components/Image.h"
#include "Components/OverlaySlot.h"
#include "Components/TextBlock.h"

void UUThematicUIRadialSlider::NativePreConstruct()
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
		UOverlaySlot* OverlaySlot = UWidgetLayoutLibrary::SlotAsOverlaySlot(TextBlock);
		OverlaySlot->SetPadding(TextPadding);
		OverlaySlot->SetHorizontalAlignment(TextHorizontalAlignment);
		OverlaySlot->SetVerticalAlignment(TextVerticalAlignment);
		SetText(Text);
	}
	if (RadialSlider)
	{
		RadialSlider->SetValue(GetPercentage());
		UOverlaySlot* OverlaySlot = UWidgetLayoutLibrary::SlotAsOverlaySlot(RadialSlider);
		OverlaySlot->SetPadding(RadialSliderPadding);
		RadialSlider->SetSliderHandleStartAngle(StartAndEndAngles.X);
		RadialSlider->SetSliderHandleEndAngle(StartAndEndAngles.Y);
		RadialSlider->SetShowSliderHand(bShowSliderHandle);
		RadialSlider->SetShowSliderHandle(bShowSliderThumb);
		RadialSlider->WidgetStyle.BarThickness = BarThickness;
		
		FSlateBrush NoDrawTypeBrush = FSlateBrush();
        NoDrawTypeBrush.DrawAs = ESlateBrushDrawType::NoDrawType;
        RadialSlider->WidgetStyle.NormalBarImage = NoDrawTypeBrush;
        RadialSlider->WidgetStyle.HoveredBarImage = NoDrawTypeBrush;
	}
	if (Image)
	{
		UOverlaySlot* OverlaySlot = UWidgetLayoutLibrary::SlotAsOverlaySlot(Image);
		OverlaySlot->SetPadding(ImagePadding);
		OverlaySlot->SetHorizontalAlignment(HAlign_Fill);
		OverlaySlot->SetVerticalAlignment(VAlign_Fill);
	}
}

void UUThematicUIRadialSlider::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (RadialSlider)
	{
		RadialSlider->OnValueChanged.AddUniqueDynamic(this, &UUThematicUIRadialSlider::HandleFloatValueChanged);
		RadialSlider->OnControllerCaptureBegin.AddUniqueDynamic(this, &UUThematicUIRadialSlider::HandleControllerFocus);
		RadialSlider->OnControllerCaptureEnd.AddUniqueDynamic(this, &UUThematicUIRadialSlider::HandleControllerUnFocused);
	}
	SetStepAmount(StepAmount);
}

void UUThematicUIRadialSlider::SetThemeNormal()
{
	Super::SetThemeNormal();
	
	if (RadialSlider && Image && TextBlock && WidgetTheme)
	{
		// Set Slider Theme
		FSlateBrush ThumbBrush = ThumbImage;
		ThumbBrush.TintColor = ThumbBrush.TintColor.GetSpecifiedColor() * ActualThemeData.NormalTheme.Image.TintColor.GetSpecifiedColor();
		RadialSlider->WidgetStyle.NormalThumbImage = ThumbBrush;
		RadialSlider->WidgetStyle.HoveredThumbImage = ThumbBrush;
		RadialSlider->SetSliderProgressColor(ActualThemeData.NormalTheme.FillColor);
		RadialSlider->SetSliderBarColor(ActualThemeData.NormalTheme.Image.TintColor.GetSpecifiedColor());
		
		// Set Image Theme
		FSlateBrush ImageBrush = ActualThemeData.NormalTheme.Image;
		ImageBrush.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
		Image->SetBrush(ImageBrush);
		
		// Set TextBlock Theme
		TextBlock->SetFont(ActualThemeData.NormalTheme.TextFont);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UUThematicUIRadialSlider::SetThemeNormal : UUThematicUIRadialSlider::RadialSlider == nullptr || UUThematicUIRadialSlider::Image == nullptr || UUThematicUIRadialSlider::TextBlock == nullptr || UUThematicUIRadialSlider::WidgetTheme == nullptr");
	}
}

void UUThematicUIRadialSlider::SetThemeHovered()
{
	Super::SetThemeHovered();
	
	if (RadialSlider && Image && TextBlock && WidgetTheme)
	{
		// Set Slider Theme
		FSlateBrush ThumbBrush = ThumbImage;
		ThumbBrush.TintColor = ThumbBrush.TintColor.GetSpecifiedColor() * ActualThemeData.HoveredTheme.Image.TintColor.GetSpecifiedColor();
		RadialSlider->WidgetStyle.NormalThumbImage = ThumbBrush;
		RadialSlider->WidgetStyle.HoveredThumbImage = ThumbBrush;
		RadialSlider->SetSliderProgressColor(ActualThemeData.HoveredTheme.FillColor);
		RadialSlider->SetSliderBarColor(ActualThemeData.HoveredTheme.Image.TintColor.GetSpecifiedColor());
		
		// Set Image Theme
		FSlateBrush ImageBrush = ActualThemeData.HoveredTheme.Image;
		ImageBrush.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
		Image->SetBrush(ImageBrush);
		
		// Set TextBlock Theme
		TextBlock->SetFont(ActualThemeData.HoveredTheme.TextFont);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UUThematicUIRadialSlider::SetThemeHovered : UUThematicUIRadialSlider::RadialSlider == nullptr || UUThematicUIRadialSlider::Image == nullptr || UUThematicUIRadialSlider::TextBlock == nullptr || UUThematicUIRadialSlider::WidgetTheme == nullptr");
	}
}

void UUThematicUIRadialSlider::SetThemePressed()
{
	Super::SetThemePressed();
	
	if (RadialSlider && Image && TextBlock && WidgetTheme)
	{
		// Set Slider Theme
		FSlateBrush ThumbBrush = ThumbImage;
		ThumbBrush.TintColor = ThumbBrush.TintColor.GetSpecifiedColor() * ActualThemeData.PressedTheme.Image.TintColor.GetSpecifiedColor();
		RadialSlider->WidgetStyle.NormalThumbImage = ThumbBrush;
		RadialSlider->WidgetStyle.HoveredThumbImage = ThumbBrush;
		RadialSlider->SetSliderProgressColor(ActualThemeData.PressedTheme.FillColor);
		RadialSlider->SetSliderBarColor(ActualThemeData.PressedTheme.Image.TintColor.GetSpecifiedColor());
		
		// Set Image Theme
		FSlateBrush ImageBrush = ActualThemeData.PressedTheme.Image;
		ImageBrush.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
		Image->SetBrush(ImageBrush);
		
		// Set TextBlock Theme
		TextBlock->SetFont(ActualThemeData.PressedTheme.TextFont);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UUThematicUIRadialSlider::SetThemePressed : UUThematicUIRadialSlider::RadialSlider == nullptr || UUThematicUIRadialSlider::Image == nullptr || UUThematicUIRadialSlider::TextBlock == nullptr || UUThematicUIRadialSlider::WidgetTheme == nullptr");
	}
}

FReply UUThematicUIRadialSlider::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	if (RadialSlider)
	{
		return FReply::Handled().SetUserFocus(RadialSlider->TakeWidget(), InFocusEvent.GetCause());
	}
	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

FVector2D UUThematicUIRadialSlider::GetValueRange() const
{
	return ValueRange;
}

void UUThematicUIRadialSlider::SetValueRange(const FVector2D& NewValueRange)
{
	ValueRange = NewValueRange;
	
	RadialSlider->StepSize = UpdateSteppingSize();
	
	CurrentValue = CalculateCurrentValue(RadialSlider->GetValue());
}

float UUThematicUIRadialSlider::GetStepAmount() const
{
	return StepAmount;
}

void UUThematicUIRadialSlider::SetStepAmount(const float NewStepAmount)
{
	StepAmount = NewStepAmount;
	
	if (RadialSlider)
	{
		RadialSlider->SetStepSize(UpdateSteppingSize());
	}
}

float UUThematicUIRadialSlider::GetCurrentValue() const
{
	return CurrentValue;
}

void UUThematicUIRadialSlider::SetText(const FText& NewText)
{
	Text = NewText;
	
	if (Text.IsEmptyOrWhitespace() && !bAlwaysDisplayValue)
	{
		TextBlock->SetText(Text);
		return;
	}
	
#define LOCTEXT_NAMESPACE "Text"
	FText ActualText = Text;
	FText Delimiter = FText();
	if (!Text.IsEmptyOrWhitespace()) Delimiter = FText::FromString(":");
	FFormatNamedArguments Args;
	Args.Add(TEXT("Text"), ActualText);
	Args.Add(TEXT("Delimiter"), Delimiter);
	Args.Add(TEXT("Float"), FText::AsNumber(CurrentValue));
	ActualText = FText().Format(LOCTEXT("Text", "{Text}{Delimiter} {Float}"), Args);
	TextBlock->SetText(ActualText);
#undef LOCTEXT_NAMESPACE
}

float UUThematicUIRadialSlider::GetPercentage() const
{
	return ((CurrentValue - ValueRange.X) / (ValueRange.Y - ValueRange.X));
}

float UUThematicUIRadialSlider::CalculateCurrentValue(const float Percentage) const
{
	float Value = ValueRange.Y - ValueRange.X;
	Value *= Percentage;
	Value += ValueRange.X;
	Value = FMath::Clamp(Value, ValueRange.X, ValueRange.Y);
	return Value;
}

float UUThematicUIRadialSlider::UpdateSteppingSize() const
{
	float Percentage = GetPercentage();
	Percentage = (CurrentValue - ValueRange.X + StepAmount) / (ValueRange.Y - ValueRange.X) - Percentage;
	return Percentage;
}

void UUThematicUIRadialSlider::HandleFloatValueChanged(const float NewValue)
{
	CurrentValue = CalculateCurrentValue(NewValue);
	SetText(Text);
	TUiValueChanged.Broadcast(CurrentValue);
}

void UUThematicUIRadialSlider::HandleControllerFocus()
{
	SetThemePressed();
	if (USoundBase* SoundBase = Cast<USoundBase>(ActualThemeData.PressedTheme.Sound.GetResourceObject()))
		PlaySound(SoundBase);
}

void UUThematicUIRadialSlider::HandleControllerUnFocused()
{
	if (RadialSlider->HasAnyUserFocus())
		SetThemeHovered();
}
