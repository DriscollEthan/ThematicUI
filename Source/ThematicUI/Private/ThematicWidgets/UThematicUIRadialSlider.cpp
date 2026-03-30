// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/UThematicUIRadialSlider.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"
#include "Components/RadialSlider.h"
#include "Components/Image.h"
#include "Components/OverlaySlot.h"
#include "Components/TextBlock.h"

#include "Sound/SoundBase.h"

const FVector2D& UUThematicUIRadialSlider::GetSizeBoxSize() const
{
	return SizeBoxSize;
}

void UUThematicUIRadialSlider::SetSizeBoxSize(const FVector2D& NewSizeBoxSize)
{
	SizeBoxSize = NewSizeBoxSize;
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(SizeBoxSize.X);
		SizeBox->SetHeightOverride(SizeBoxSize.Y);
	}
}

const float UUThematicUIRadialSlider::GetCurrentValue() const
{
	return CurrentValue;
}

void UUThematicUIRadialSlider::SetCurrentValue(const float NewCurrentValue)
{
	CurrentValue = NewCurrentValue;
	
	if (RadialSlider)
	{
		RadialSlider->SetValue(GetPercentage());
	}
	
	SetText(Text);
}

const FVector2D& UUThematicUIRadialSlider::GetValueRange() const
{
	return ValueRange;
}

void UUThematicUIRadialSlider::SetValueRange(const FVector2D& NewValueRange)
{
	ValueRange = NewValueRange;
	
	float Percentage = GetPercentage();
	Percentage = (CurrentValue - ValueRange.X + StepAmount) / (ValueRange.Y - ValueRange.X) - Percentage;
	
	RadialSlider->StepSize = Percentage;
	
	CurrentValue = CalculateCurrentValue(Percentage);
}

const float UUThematicUIRadialSlider::GetStepAmount() const
{
	return StepAmount;
}

void UUThematicUIRadialSlider::SetStepAmount(const float NewStepAmount)
{
	StepAmount = NewStepAmount;
	
	float Percentage = GetPercentage();
	Percentage = (CurrentValue - ValueRange.X + StepAmount) / (ValueRange.Y - ValueRange.X) - Percentage;
	
	if (RadialSlider)
	{
		RadialSlider->SetStepSize(Percentage);
	}
}

const FVector2D& UUThematicUIRadialSlider::GetStartAndEndAngles() const
{
	return StartAndEndAngles;
}

void UUThematicUIRadialSlider::SetStartAndEndAngles(const FVector2D& NewStartAndEndAngles)
{
	StartAndEndAngles = NewStartAndEndAngles;
	
	if (RadialSlider)
	{
		RadialSlider->SetSliderHandleStartAngle(StartAndEndAngles.X);
		RadialSlider->SetSliderHandleEndAngle(StartAndEndAngles.Y);
	}
}

const float UUThematicUIRadialSlider::GetBarThickness() const
{
	return BarThickness;
}

void UUThematicUIRadialSlider::SetBarThickness(const float NewBarThickness)
{
	BarThickness = NewBarThickness;
	
	if (RadialSlider)
	{
		RadialSlider->WidgetStyle.BarThickness = BarThickness;
	}
}

const bool UUThematicUIRadialSlider::GetbShowSliderThumb() const
{
	return bShowSliderThumb;
}

void UUThematicUIRadialSlider::SetbShowSliderThumb(const bool bNewShowSliderThumb)
{
	bShowSliderThumb = bNewShowSliderThumb;
	
	if (RadialSlider)
	{
		RadialSlider->SetShowSliderHandle(bShowSliderThumb);
	}
}

const bool UUThematicUIRadialSlider::GetbShowSliderHandle() const
{
	return bShowSliderHandle;
}

void UUThematicUIRadialSlider::SetbShowSliderHandle(const bool bNewShowSliderHandle)
{
	bShowSliderHandle = bNewShowSliderHandle;
	
	if (RadialSlider)
	{
		RadialSlider->SetShowSliderHand(bShowSliderHandle);
	}
}

const FSlateBrush& UUThematicUIRadialSlider::GetThumbImage() const
{
	return ThumbImage;
}

void UUThematicUIRadialSlider::SetThumbImage(const FSlateBrush& NewThumbImage)
{
	ThumbImage = NewThumbImage;
}

const float UUThematicUIRadialSlider::GetRadialSliderPadding() const
{
	return RadialSliderPadding;
}

void UUThematicUIRadialSlider::SetRadialSliderPadding(const float NewRadialSliderPadding)
{
	RadialSliderPadding = NewRadialSliderPadding;
	
	if (RadialSlider)
	{
		UOverlaySlot* OverlaySlot = UWidgetLayoutLibrary::SlotAsOverlaySlot(RadialSlider);
		OverlaySlot->SetPadding(RadialSliderPadding);
	}
}

const FMargin& UUThematicUIRadialSlider::GetImagePadding() const
{
	return ImagePadding;
}

void UUThematicUIRadialSlider::SetImagePadding(const FMargin& NewImagePadding)
{
	ImagePadding = NewImagePadding;
	
	if (Image)
	{
		UOverlaySlot* OverlaySlot = UWidgetLayoutLibrary::SlotAsOverlaySlot(Image);
		OverlaySlot->SetPadding(ImagePadding);
	}
}

const EHorizontalAlignment UUThematicUIRadialSlider::GetTextHorizontalAlignment() const
{
	return TextHorizontalAlignment;
}

void UUThematicUIRadialSlider::SetTextHorizontalAlignment(const EHorizontalAlignment& NewTextHorizontalAlignment)
{
	TextHorizontalAlignment = NewTextHorizontalAlignment;
	
	if (TextBlock)
	{
		UOverlaySlot* OverlaySlot = UWidgetLayoutLibrary::SlotAsOverlaySlot(TextBlock);
		OverlaySlot->SetHorizontalAlignment(TextHorizontalAlignment);
	}
}

const EVerticalAlignment UUThematicUIRadialSlider::GetTextVerticalAlignment() const
{
	return TextVerticalAlignment;
}

void UUThematicUIRadialSlider::SetTextVerticalAlignment(const EVerticalAlignment& NewTextVerticalAlignment)
{
	this->TextVerticalAlignment = NewTextVerticalAlignment;
	
	if (TextBlock)
	{
		UOverlaySlot* OverlaySlot = UWidgetLayoutLibrary::SlotAsOverlaySlot(TextBlock);
		OverlaySlot->SetVerticalAlignment(TextVerticalAlignment);
	}
}

const FText& UUThematicUIRadialSlider::GetText() const
{
	return Text;
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

const bool UUThematicUIRadialSlider::GetbAlwaysDisplayValue() const
{
	return bAlwaysDisplayValue;
}

void UUThematicUIRadialSlider::SetbAlwaysDisplayValue(const bool bNewAlwaysDisplayValue)
{
	bAlwaysDisplayValue = bNewAlwaysDisplayValue;
}

const FMargin& UUThematicUIRadialSlider::GetTextPadding() const
{
	return TextPadding;
}

void UUThematicUIRadialSlider::SetTextPadding(const FMargin& NewTextPadding)
{
	this->TextPadding = NewTextPadding;
	
	if (TextBlock)
	{
		UOverlaySlot* OverlaySlot = UWidgetLayoutLibrary::SlotAsOverlaySlot(TextBlock);
		OverlaySlot->SetPadding(TextPadding);
	}
}

const bool UUThematicUIRadialSlider::GetbShowValueAsPercentage() const
{
	return bShowValueAsPercentage;
}

void UUThematicUIRadialSlider::SetbShowValueAsPercentage(const bool NewbShowValueAsPercentage)
{
	bShowValueAsPercentage = NewbShowValueAsPercentage;
	SetText(Text);
}


const float UUThematicUIRadialSlider::GetPercentage() const
{
	return ((CurrentValue - ValueRange.X) / (ValueRange.Y - ValueRange.X));
}

const float UUThematicUIRadialSlider::CalculateCurrentValue(const float Percentage) const
{
	float Value = ValueRange.Y - ValueRange.X;
	Value *= Percentage;
	Value += ValueRange.X;
	Value = FMath::Clamp(Value, ValueRange.X, ValueRange.Y);
	return Value;
}

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
