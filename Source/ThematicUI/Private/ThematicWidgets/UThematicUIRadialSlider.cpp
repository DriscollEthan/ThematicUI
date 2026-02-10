// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/UThematicUIRadialSlider.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"
#include "Runtime/AdvancedWidgets/Public/Components/RadialSlider.h"
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
		SetText(Text);
		UOverlaySlot* OverlaySlot = UWidgetLayoutLibrary::SlotAsOverlaySlot(Image);
		OverlaySlot->SetPadding(TextPadding);
		OverlaySlot->SetHorizontalAlignment(TextHorizontalAlignment);
		OverlaySlot->SetVerticalAlignment(TextVerticalAlignment);
	}
	if (RadialSlider)
	{
		RadialSlider->Value = GetPercentage();
		UOverlaySlot* OverlaySlot = UWidgetLayoutLibrary::SlotAsOverlaySlot(Image);
		OverlaySlot->SetPadding(RadialSliderPadding);
	}
	if (Image)
	{
		UOverlaySlot* OverlaySlot = UWidgetLayoutLibrary::SlotAsOverlaySlot(Image);
		OverlaySlot->SetPadding(ImagePadding);
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
}

void UUThematicUIRadialSlider::SetThemeHovered()
{
	Super::SetThemeHovered();
}

void UUThematicUIRadialSlider::SetThemePressed()
{
	Super::SetThemePressed();
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
		RadialSlider->StepSize = UpdateSteppingSize();
	}
}

float UUThematicUIRadialSlider::GetCurrentValue() const
{
	return CurrentValue;
}

void UUThematicUIRadialSlider::SetText(const FText& NewText)
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
	TUiValueChanged.Broadcast();
}

void UUThematicUIRadialSlider::HandleControllerFocus()
{
	SetThemePressed();
}

void UUThematicUIRadialSlider::HandleControllerUnFocused()
{
	if (RadialSlider->HasAnyUserFocus())
		SetThemeHovered();
}
