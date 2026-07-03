// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/ThematicUIInteractable.h"
 
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

const FThematicUIThemeDataOverride& UThematicUIInteractable::GetWidgetThemeOverrideData() const
{
	return WidgetThemeOverrideData;
}

void UThematicUIInteractable::SetWidgetThemeOverrideData(const FThematicUIThemeDataOverride& NewWidgetThemeOverrideData)
{
	WidgetThemeOverrideData = NewWidgetThemeOverrideData;
	
	CalculateAndSetActualWidgetThemeData();
}

void UThematicUIInteractable::SetWidgetNormalThemeOverrideDate(const FThematicUIThemeOverride& NewWidgetNormalThemeOverride)
{
	WidgetThemeOverrideData.NormalThemeOverride = NewWidgetNormalThemeOverride;
	
	CalculateAndSetActualWidgetThemeData();
}

void UThematicUIInteractable::SetWidgetHoveredThemeOverrideDate(const FThematicUIThemeOverride& NewWidgetHoveredThemeOverride)
{
	WidgetThemeOverrideData.HoveredThemeOverride = NewWidgetHoveredThemeOverride;
	
	CalculateAndSetActualWidgetThemeData();
}

void UThematicUIInteractable::SetWidgetPressedThemeOverrideDate(const FThematicUIThemeOverride& NewWidgetPressedThemeOverride)
{
	WidgetThemeOverrideData.PressedThemeOverride = NewWidgetPressedThemeOverride;
	
	CalculateAndSetActualWidgetThemeData();
}

const FThematicUIThemeData& UThematicUIInteractable::GetActualThemeData() const
{
	return ActualThemeData;
}

void UThematicUIInteractable::CalculateAndSetActualWidgetThemeData()
{
	// Figure Out ActualThemeData after overrides
	if (WidgetTheme)
	{
		ActualThemeData = WidgetThemeOverrideData.ConvertToThemeData(WidgetTheme->GetThematicUIThemeData());
	}
	else
	{
		ActualThemeData = WidgetThemeOverrideData.ConvertToThemeData();
	}
	
}

void UThematicUIInteractable::SetSizeBoxSize(const FVector2D& NewSizeBoxSize)
{
	SizeBoxSize = NewSizeBoxSize;
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(SizeBoxSize.X);
		SizeBox->SetHeightOverride(SizeBoxSize.Y);
	}
}

void UThematicUIInteractable::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	SetIsFocusable(true);
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(SizeBoxSize.X);
		SizeBox->SetHeightOverride(SizeBoxSize.Y);
	}
	
	CalculateAndSetActualWidgetThemeData();
	
	SetThemeNormal();
}

void UThematicUIInteractable::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (IsFocusable())
	{
		Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	
		if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), InMouseEvent.GetUserIndex()))
		{
			this->SetUserFocus(PC);
		}
	}
}

void UThematicUIInteractable::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
 {
	Super::NativeOnAddedToFocusPath(InFocusEvent);
	
	SetThemeHovered();
	if (USoundBase* SoundBase = Cast<USoundBase>(ActualThemeData.HoveredTheme.Sound.GetResourceObject()))
		PlaySound(SoundBase);
}

void UThematicUIInteractable::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusLost(InFocusEvent);
	
	SetThemeNormal();
	if (USoundBase* SoundBase = Cast<USoundBase>(ActualThemeData.NormalTheme.Sound.GetResourceObject()))
		PlaySound(SoundBase);
}

void UThematicUIInteractable::SetThemeNormal()
{
	UE_LOGFMT(LogThematicUI, Log, "{Name} is setting theme to normal settings", GetName());
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(SizeBoxSize.X);
		SizeBox->SetHeightOverride(SizeBoxSize.Y);
	}
	
	OnTuiInteractableSetToNormalTheme.Broadcast(this);
}

void UThematicUIInteractable::SetThemeHovered()
{
	UE_LOGFMT(LogThematicUI, Log, "{Name} is setting theme to hovered settings", GetName());
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(SizeBoxSize.X * SizeBoxHoveredSizeMultiplier.X);
		SizeBox->SetHeightOverride(SizeBoxSize.Y * SizeBoxHoveredSizeMultiplier.Y);
	}
	
	OnTuiInteractableSetToHoveredTheme.Broadcast(this);
}

void UThematicUIInteractable::SetThemePressed()
{
	UE_LOGFMT(LogThematicUI, Log, "{Name} is setting theme to pressed settings", GetName());
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(SizeBoxSize.X * SizeBoxPressedSizeMultiplier.X);
		SizeBox->SetHeightOverride(SizeBoxSize.Y * SizeBoxPressedSizeMultiplier.Y);
	}
	
	OnTuiInteractableSetToPressedTheme.Broadcast(this);
}