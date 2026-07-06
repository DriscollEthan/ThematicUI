// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/ThematicUIInteractable.h"
 
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"


const FThematicUIMainWidgetData& UThematicUIInteractable::GetPrimaryWidgetData() const
{
	return PrimaryWidgetData;
}

void UThematicUIInteractable::SetPrimaryWidgetData(const FThematicUIMainWidgetData& NewPrimaryWidgetData)
{
	PrimaryWidgetData = NewPrimaryWidgetData;
	
	CalculateAndSetActualWidgetThemeData();
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(PrimaryWidgetData.SizeBoxSize.X);
		SizeBox->SetHeightOverride(PrimaryWidgetData.SizeBoxSize.Y);
	}
}


const FThematicUIThemeData& UThematicUIInteractable::GetActualThemeData() const
{
	return ActualThemeData;
}

UThematicUIThemeDataAsset* UThematicUIInteractable::GetWidgetTheme() const
{
	return PrimaryWidgetData.WidgetTheme;
}

void UThematicUIInteractable::SetWidgetTheme(UThematicUIThemeDataAsset* NewWidgetTheme)
{
	PrimaryWidgetData.WidgetTheme = NewWidgetTheme;
	
	CalculateAndSetActualWidgetThemeData();
}

const FThematicUIThemeDataOverride& UThematicUIInteractable::GetWidgetThemeOverrideData() const
{
	return PrimaryWidgetData.WidgetThemeOverrideData;
}

void UThematicUIInteractable::SetWidgetThemeOverrideData(FThematicUIThemeDataOverride NewWidgetThemeOverrideData)
{
	PrimaryWidgetData.WidgetThemeOverrideData = NewWidgetThemeOverrideData;
	
	CalculateAndSetActualWidgetThemeData();
}

const FVector2D& UThematicUIInteractable::GetSizeBoxSize() const
{
	return PrimaryWidgetData.SizeBoxSize;
}

void UThematicUIInteractable::SetSizeBoxSize(const FVector2D& NewSizeBoxSize)
{
	PrimaryWidgetData.SizeBoxSize = NewSizeBoxSize;
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(PrimaryWidgetData.SizeBoxSize.X);
		SizeBox->SetHeightOverride(PrimaryWidgetData.SizeBoxSize.Y);
	}
}

const FVector2D& UThematicUIInteractable::GetSizeBoxHoveredSizeMultiplier() const
{
	return PrimaryWidgetData.SizeBoxHoveredSizeMultiplier;
}

void UThematicUIInteractable::SetSizeBoxHoveredSizeMultiplier(const FVector2D& NewGetSizeBoxHoveredSizeMultiplier)
{
	PrimaryWidgetData.SizeBoxHoveredSizeMultiplier = NewGetSizeBoxHoveredSizeMultiplier;
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(GetSizeBoxSize().X * GetSizeBoxHoveredSizeMultiplier().X);
		SizeBox->SetHeightOverride(GetSizeBoxSize().Y * GetSizeBoxHoveredSizeMultiplier().Y);
	}
}

const FVector2D& UThematicUIInteractable::GetSizeBoxPressedSizeMultiplier() const
{
	return PrimaryWidgetData.SizeBoxPressedSizeMultiplier;
}

void UThematicUIInteractable::SetSizeBoxPressedSizeMultiplier(const FVector2D& NewSizeBoxPressedSizeMultiplier)
{
	PrimaryWidgetData.SizeBoxPressedSizeMultiplier = NewSizeBoxPressedSizeMultiplier;
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(GetSizeBoxSize().X * GetSizeBoxPressedSizeMultiplier().X);
		SizeBox->SetHeightOverride(GetSizeBoxSize().Y * GetSizeBoxPressedSizeMultiplier().Y);
	}
}

void UThematicUIInteractable::CalculateAndSetActualWidgetThemeData()
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

void UThematicUIInteractable::NativePreConstruct()
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
		SizeBox->SetWidthOverride(GetSizeBoxSize().X);
		SizeBox->SetHeightOverride(GetSizeBoxSize().Y);
	}
	
	OnTuiInteractableSetToNormalTheme.Broadcast(this);
}

void UThematicUIInteractable::SetThemeHovered()
{
	UE_LOGFMT(LogThematicUI, Log, "{Name} is setting theme to hovered settings", GetName());
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(GetSizeBoxSize().X * GetSizeBoxHoveredSizeMultiplier().X);
		SizeBox->SetHeightOverride(GetSizeBoxSize().Y * GetSizeBoxHoveredSizeMultiplier().Y);
	}
	
	OnTuiInteractableSetToHoveredTheme.Broadcast(this);
}

void UThematicUIInteractable::SetThemePressed()
{
	UE_LOGFMT(LogThematicUI, Log, "{Name} is setting theme to pressed settings", GetName());
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(GetSizeBoxSize().X * GetSizeBoxPressedSizeMultiplier().X);
		SizeBox->SetHeightOverride(GetSizeBoxSize().Y * GetSizeBoxPressedSizeMultiplier().Y);
	}
	
	OnTuiInteractableSetToPressedTheme.Broadcast(this);
}