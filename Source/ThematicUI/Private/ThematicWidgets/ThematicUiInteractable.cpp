// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/ThematicUiInteractable.h"

#include <Misc/DataValidation.h>

#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"



const FThematicUIMainWidgetData& UThematicUiInteractable::GetPrimaryWidgetData() const
{
	return PrimaryWidgetData;
}

void UThematicUiInteractable::SetPrimaryWidgetData(const FThematicUIMainWidgetData& NewPrimaryWidgetData)
{
	PrimaryWidgetData = NewPrimaryWidgetData;
	
	CalculateAndSetActualWidgetThemeData();
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(PrimaryWidgetData.SizeBoxSize.X);
		SizeBox->SetHeightOverride(PrimaryWidgetData.SizeBoxSize.Y);
	}
}


const FThematicUiThemeData& UThematicUiInteractable::GetActualThemeData() const
{
	return ActualThemeData;
}

UThematicUiThemeDataAsset* UThematicUiInteractable::GetWidgetTheme() const
{
	return PrimaryWidgetData.WidgetTheme;
}

void UThematicUiInteractable::SetWidgetTheme(UThematicUiThemeDataAsset* NewWidgetTheme)
{
	PrimaryWidgetData.WidgetTheme = NewWidgetTheme;
	
	CalculateAndSetActualWidgetThemeData();
}

const FThematicUIThemeDataOverride& UThematicUiInteractable::GetWidgetThemeOverrideData() const
{
	return PrimaryWidgetData.WidgetThemeOverrideData;
}

void UThematicUiInteractable::SetWidgetThemeOverrideData(FThematicUIThemeDataOverride NewWidgetThemeOverrideData)
{
	PrimaryWidgetData.WidgetThemeOverrideData = NewWidgetThemeOverrideData;
	
	CalculateAndSetActualWidgetThemeData();
}

const FVector2D& UThematicUiInteractable::GetSizeBoxSize() const
{
	return PrimaryWidgetData.SizeBoxSize;
}

void UThematicUiInteractable::SetSizeBoxSize(const FVector2D& NewSizeBoxSize)
{
	PrimaryWidgetData.SizeBoxSize = NewSizeBoxSize;
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(PrimaryWidgetData.SizeBoxSize.X);
		SizeBox->SetHeightOverride(PrimaryWidgetData.SizeBoxSize.Y);
	}
}

const FVector2D& UThematicUiInteractable::GetSizeBoxHoveredSizeMultiplier() const
{
	return PrimaryWidgetData.SizeBoxHoveredSizeMultiplier;
}

void UThematicUiInteractable::SetSizeBoxHoveredSizeMultiplier(const FVector2D& NewGetSizeBoxHoveredSizeMultiplier)
{
	PrimaryWidgetData.SizeBoxHoveredSizeMultiplier = NewGetSizeBoxHoveredSizeMultiplier;
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(GetSizeBoxSize().X * GetSizeBoxHoveredSizeMultiplier().X);
		SizeBox->SetHeightOverride(GetSizeBoxSize().Y * GetSizeBoxHoveredSizeMultiplier().Y);
	}
}

const FVector2D& UThematicUiInteractable::GetSizeBoxPressedSizeMultiplier() const
{
	return PrimaryWidgetData.SizeBoxPressedSizeMultiplier;
}

void UThematicUiInteractable::SetSizeBoxPressedSizeMultiplier(const FVector2D& NewSizeBoxPressedSizeMultiplier)
{
	PrimaryWidgetData.SizeBoxPressedSizeMultiplier = NewSizeBoxPressedSizeMultiplier;
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(GetSizeBoxSize().X * GetSizeBoxPressedSizeMultiplier().X);
		SizeBox->SetHeightOverride(GetSizeBoxSize().Y * GetSizeBoxPressedSizeMultiplier().Y);
	}
}

void UThematicUiInteractable::CalculateAndSetActualWidgetThemeData()
{
	// Figure Out ActualThemeData after overrides
	if (GetWidgetTheme())
	{
		ActualThemeData = GetWidgetThemeOverrideData().ConvertToThemeData(GetWidgetTheme()->GetThematicUIThemeData());
	}
	else
	{
		ActualThemeData = GetWidgetThemeOverrideData().ConvertToThemeData();
	}
	
}

EDataValidationResult UThematicUiInteractable::IsDataValid(FDataValidationContext& Context) const
{
	return Super::IsDataValid(Context);
}

void UThematicUiInteractable::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	SetIsFocusable(true);
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(GetSizeBoxSize().X);
		SizeBox->SetHeightOverride(GetSizeBoxSize().Y);
	}
	
	CalculateAndSetActualWidgetThemeData();
	
	SetThemeNormal();
}

void UThematicUiInteractable::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
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

void UThematicUiInteractable::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
 {
	Super::NativeOnAddedToFocusPath(InFocusEvent);
	
	SetThemeHovered();
	if (USoundBase* SoundBase = Cast<USoundBase>(ActualThemeData.HoveredTheme.Sound.GetResourceObject()))
		PlaySound(SoundBase);
}

void UThematicUiInteractable::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusLost(InFocusEvent);
	
	SetThemeNormal();
	if (USoundBase* SoundBase = Cast<USoundBase>(ActualThemeData.NormalTheme.Sound.GetResourceObject()))
		PlaySound(SoundBase);
}

void UThematicUiInteractable::SetThemeNormal()
{
	UE_LOGFMT(LogThematicUI, Log, "{Name} is setting theme to normal settings", GetName());
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(GetSizeBoxSize().X);
		SizeBox->SetHeightOverride(GetSizeBoxSize().Y);
	}
	
	OnTuiInteractableSetToNormalTheme.Broadcast(this);
}

void UThematicUiInteractable::SetThemeHovered()
{
	UE_LOGFMT(LogThematicUI, Log, "{Name} is setting theme to hovered settings", GetName());
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(GetSizeBoxSize().X * GetSizeBoxHoveredSizeMultiplier().X);
		SizeBox->SetHeightOverride(GetSizeBoxSize().Y * GetSizeBoxHoveredSizeMultiplier().Y);
	}
	
	OnTuiInteractableSetToHoveredTheme.Broadcast(this);
}

void UThematicUiInteractable::SetThemePressed()
{
	UE_LOGFMT(LogThematicUI, Log, "{Name} is setting theme to pressed settings", GetName());
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(GetSizeBoxSize().X * GetSizeBoxPressedSizeMultiplier().X);
		SizeBox->SetHeightOverride(GetSizeBoxSize().Y * GetSizeBoxPressedSizeMultiplier().Y);
	}
	
	OnTuiInteractableSetToPressedTheme.Broadcast(this);
}