// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/UThematicUiRadialSlider.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/RadialSlider.h"
#include "Components/Image.h"
#include "Components/OverlaySlot.h"
#include "Components/TextBlock.h"

#include "Sound/SoundBase.h"

const float UUThematicUiRadialSlider::GetCurrentValue() const
{
	return CurrentValue;
}

void UUThematicUiRadialSlider::SetCurrentValue(const float NewCurrentValue)
{
	CurrentValue = NewCurrentValue;
	
	if (RadialSlider)
	{
		RadialSlider->SetValue(GetPercentage());
	}
	
	SetText(Text);
}

const FVector2D& UUThematicUiRadialSlider::GetValueRange() const
{
	return ValueRange;
}

void UUThematicUiRadialSlider::SetValueRange(const FVector2D& NewValueRange)
{
	ValueRange = NewValueRange;
	
	float Percentage = GetPercentage();
	Percentage = (CurrentValue - ValueRange.X + StepAmount) / (ValueRange.Y - ValueRange.X) - Percentage;
	
	RadialSlider->StepSize = Percentage;
	
	CurrentValue = CalculateCurrentValue(Percentage);
}

const float UUThematicUiRadialSlider::GetStepAmount() const
{
	return StepAmount;
}

void UUThematicUiRadialSlider::SetStepAmount(const float NewStepAmount)
{
	StepAmount = NewStepAmount;
	
	float Percentage = GetPercentage();
	Percentage = (CurrentValue - ValueRange.X + StepAmount) / (ValueRange.Y - ValueRange.X) - Percentage;
	
	if (RadialSlider)
	{
		RadialSlider->SetStepSize(Percentage);
	}
}

const FVector2D& UUThematicUiRadialSlider::GetStartAndEndAngles() const
{
	return StartAndEndAngles;
}

void UUThematicUiRadialSlider::SetStartAndEndAngles(const FVector2D& NewStartAndEndAngles)
{
	StartAndEndAngles = NewStartAndEndAngles;
	
	if (RadialSlider)
	{
		RadialSlider->SetSliderHandleStartAngle(StartAndEndAngles.X);
		RadialSlider->SetSliderHandleEndAngle(StartAndEndAngles.Y);
	}
}

const float UUThematicUiRadialSlider::GetBarThickness() const
{
	return BarThickness;
}

void UUThematicUiRadialSlider::SetBarThickness(const float NewBarThickness)
{
	BarThickness = NewBarThickness;
	
	if (RadialSlider)
	{
		RadialSlider->WidgetStyle.BarThickness = BarThickness;
	}
}

const bool UUThematicUiRadialSlider::GetbShowSliderThumb() const
{
	return bShowSliderThumb;
}

void UUThematicUiRadialSlider::SetbShowSliderThumb(const bool bNewShowSliderThumb)
{
	bShowSliderThumb = bNewShowSliderThumb;
	
	if (RadialSlider)
	{
		RadialSlider->SetShowSliderHandle(bShowSliderThumb);
	}
}

const bool UUThematicUiRadialSlider::GetbShowSliderHandle() const
{
	return bShowSliderHandle;
}

void UUThematicUiRadialSlider::SetbShowSliderHandle(const bool bNewShowSliderHandle)
{
	bShowSliderHandle = bNewShowSliderHandle;
	
	if (RadialSlider)
	{
		RadialSlider->SetShowSliderHand(bShowSliderHandle);
	}
}

const FSlateBrush& UUThematicUiRadialSlider::GetThumbImage() const
{
	return ThumbImage;
}

void UUThematicUiRadialSlider::SetThumbImage(const FSlateBrush& NewThumbImage)
{
	ThumbImage = NewThumbImage;
	
	if (RadialSlider)
	{
		FSlateBrush ThumbBrush = ThumbImage;
		ThumbBrush.TintColor = ThumbBrush.TintColor.GetSpecifiedColor() * ActualThemeData.NormalTheme.Image.TintColor.GetSpecifiedColor();
		RadialSlider->WidgetStyle.NormalThumbImage = ThumbBrush;
		RadialSlider->WidgetStyle.HoveredThumbImage = ThumbBrush;
	}
}

const FSlateColor& UUThematicUiRadialSlider::GetSliderHandleColor() const
{
	return SliderHandleColor;
}

void UUThematicUiRadialSlider::SetSliderHandleColor(const FSlateColor& NewSliderHandleColor)
{
	SliderHandleColor = NewSliderHandleColor;
	
	if (RadialSlider)
	{
		RadialSlider->SetSliderBarColor(SliderHandleColor.GetSpecifiedColor());
	}
}

const float UUThematicUiRadialSlider::GetRadialSliderPadding() const
{
	return RadialSliderPadding;
}

void UUThematicUiRadialSlider::SetRadialSliderPadding(const float NewRadialSliderPadding)
{
	RadialSliderPadding = NewRadialSliderPadding;
	
	if (RadialSlider)
	{
		UOverlaySlot* OverlaySlot = UWidgetLayoutLibrary::SlotAsOverlaySlot(RadialSlider);
		OverlaySlot->SetPadding(RadialSliderPadding);
	}
}

const FMargin& UUThematicUiRadialSlider::GetImagePadding() const
{
	return ImagePadding;
}

void UUThematicUiRadialSlider::SetImagePadding(const FMargin& NewImagePadding)
{
	ImagePadding = NewImagePadding;
	
	if (Image)
	{
		UOverlaySlot* OverlaySlot = UWidgetLayoutLibrary::SlotAsOverlaySlot(Image);
		OverlaySlot->SetPadding(ImagePadding);
	}
}

const EHorizontalAlignment UUThematicUiRadialSlider::GetTextHorizontalAlignment() const
{
	return TextHorizontalAlignment;
}

void UUThematicUiRadialSlider::SetTextHorizontalAlignment(const EHorizontalAlignment& NewTextHorizontalAlignment)
{
	TextHorizontalAlignment = NewTextHorizontalAlignment;
	
	if (TextBlock)
	{
		UOverlaySlot* OverlaySlot = UWidgetLayoutLibrary::SlotAsOverlaySlot(TextBlock);
		OverlaySlot->SetHorizontalAlignment(TextHorizontalAlignment);
	}
}

const EVerticalAlignment UUThematicUiRadialSlider::GetTextVerticalAlignment() const
{
	return TextVerticalAlignment;
}

void UUThematicUiRadialSlider::SetTextVerticalAlignment(const EVerticalAlignment& NewTextVerticalAlignment)
{
	this->TextVerticalAlignment = NewTextVerticalAlignment;
	
	if (TextBlock)
	{
		UOverlaySlot* OverlaySlot = UWidgetLayoutLibrary::SlotAsOverlaySlot(TextBlock);
		OverlaySlot->SetVerticalAlignment(TextVerticalAlignment);
	}
}

const FText& UUThematicUiRadialSlider::GetText() const
{
	return Text;
}

void UUThematicUiRadialSlider::SetText(const FText& NewText)
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

const bool UUThematicUiRadialSlider::GetbAlwaysDisplayValue() const
{
	return bAlwaysDisplayValue;
}

void UUThematicUiRadialSlider::SetbAlwaysDisplayValue(const bool bNewAlwaysDisplayValue)
{
	bAlwaysDisplayValue = bNewAlwaysDisplayValue;
}

const FMargin& UUThematicUiRadialSlider::GetTextPadding() const
{
	return TextPadding;
}

void UUThematicUiRadialSlider::SetTextPadding(const FMargin& NewTextPadding)
{
	this->TextPadding = NewTextPadding;
	
	if (TextBlock)
	{
		UOverlaySlot* OverlaySlot = UWidgetLayoutLibrary::SlotAsOverlaySlot(TextBlock);
		OverlaySlot->SetPadding(TextPadding);
	}
}

const bool UUThematicUiRadialSlider::GetbShowValueAsPercentage() const
{
	return bShowValueAsPercentage;
}

void UUThematicUiRadialSlider::SetbShowValueAsPercentage(const bool NewbShowValueAsPercentage)
{
	bShowValueAsPercentage = NewbShowValueAsPercentage;
	SetText(Text);
}


const float UUThematicUiRadialSlider::GetPercentage() const
{
	return ((CurrentValue - ValueRange.X) / (ValueRange.Y - ValueRange.X));
}

const float UUThematicUiRadialSlider::CalculateCurrentValue(const float Percentage) const
{
	float Value = ValueRange.Y - ValueRange.X;
	Value *= Percentage;
	Value += ValueRange.X;
	Value = FMath::Clamp(Value, ValueRange.X, ValueRange.Y);
	return Value;
}

void UUThematicUiRadialSlider::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	CurrentValue = CalculateCurrentValue(GetPercentage());
	
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

void UUThematicUiRadialSlider::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (RadialSlider)
	{
		RadialSlider->OnValueChanged.AddUniqueDynamic(this, &UUThematicUiRadialSlider::HandleFloatValueChanged);
		RadialSlider->OnControllerCaptureBegin.AddUniqueDynamic(this, &UUThematicUiRadialSlider::HandleControllerFocus);
		RadialSlider->OnControllerCaptureEnd.AddUniqueDynamic(this, &UUThematicUiRadialSlider::HandleControllerUnFocused);
	}
	SetStepAmount(StepAmount);
}

void UUThematicUiRadialSlider::SetThemeNormal()
{
	Super::SetThemeNormal();
	
	if (RadialSlider && Image && TextBlock)
	{
		// Set Slider Theme
		FSlateBrush ThumbBrush = ThumbImage;
		ThumbBrush.TintColor = ThumbBrush.TintColor.GetSpecifiedColor() * ActualThemeData.NormalTheme.Image.TintColor.GetSpecifiedColor();
		RadialSlider->WidgetStyle.NormalThumbImage = ThumbBrush;
		RadialSlider->WidgetStyle.HoveredThumbImage = ThumbBrush;
		RadialSlider->SetSliderProgressColor(ActualThemeData.NormalTheme.FillColor);
		RadialSlider->SetSliderBarColor(SliderHandleColor.GetSpecifiedColor());
		
		// Set Image Theme
		FSlateBrush ImageBrush = ActualThemeData.NormalTheme.Image;
		ImageBrush.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
		Image->SetBrush(ImageBrush);
		
		// Set TextBlock Theme
		TextBlock->SetFont(ActualThemeData.NormalTheme.TextFont);
		TextBlock->SetColorAndOpacity(ActualThemeData.NormalTheme.TextColor);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UUThematicUiRadialSlider::SetThemeNormal : UUThematicUiRadialSlider::RadialSlider == nullptr || UUThematicUiRadialSlider::Image == nullptr || UUThematicUiRadialSlider::TextBlock == nullptr");
	}
}

void UUThematicUiRadialSlider::SetThemeHovered()
{
	Super::SetThemeHovered();
	
	if (RadialSlider && Image && TextBlock)
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
		TextBlock->SetColorAndOpacity(ActualThemeData.HoveredTheme.TextColor);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UUThematicUiRadialSlider::SetThemeHovered : UUThematicUiRadialSlider::RadialSlider == nullptr || UUThematicUiRadialSlider::Image == nullptr || UUThematicUiRadialSlider::TextBlock == nullptr");
	}
}

void UUThematicUiRadialSlider::SetThemePressed()
{
	Super::SetThemePressed();
	
		if (RadialSlider && Image && TextBlock)
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
		TextBlock->SetColorAndOpacity(ActualThemeData.PressedTheme.TextColor);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UUThematicUiRadialSlider::SetThemePressed : UUThematicUiRadialSlider::RadialSlider == nullptr || UUThematicUiRadialSlider::Image == nullptr || UUThematicUiRadialSlider::TextBlock == nullptr");
	}
}

FReply UUThematicUiRadialSlider::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	if (RadialSlider)
	{
		return FReply::Handled().SetUserFocus(RadialSlider->TakeWidget(), InFocusEvent.GetCause());
	}
	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

void UUThematicUiRadialSlider::HandleFloatValueChanged(const float NewValue)
{
	CurrentValue = CalculateCurrentValue(NewValue);
	SetText(Text);
	TUiValueChanged.Broadcast(CurrentValue);
}

void UUThematicUiRadialSlider::HandleControllerFocus()
{
	SetThemePressed();
	if (USoundBase* SoundBase = Cast<USoundBase>(ActualThemeData.PressedTheme.Sound.GetResourceObject()))
		PlaySound(SoundBase);
}

void UUThematicUiRadialSlider::HandleControllerUnFocused()
{
	if (RadialSlider->HasAnyUserFocus())
		SetThemeHovered();
}

//EDataValidationResult UUThematicUiRadialSlider::IsDataValid(class FDataValidationContext& Context) const
//{
//	return Super::IsDataValid(Context);
//}
