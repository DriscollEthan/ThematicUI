// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/ThematicUIInteractable.h"

#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogThematicUI);

void UThematicUIInteractable::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	// Figure Out ActualThemeData after overrides
	if (WidgetTheme)
	{
		ActualThemeData = WidgetThemeOverride.ConvertToThemeData(WidgetTheme);
	}
	else
	{
		ActualThemeData = WidgetThemeOverride.ConvertToThemeData();
	}
	
	SetThemeNormal();
}

void UThematicUIInteractable::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), InMouseEvent.GetUserIndex()))
	{
		this->SetUserFocus(PC);
	}
}

void UThematicUIInteractable::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
 {
	Super::NativeOnAddedToFocusPath(InFocusEvent);
	
	SetThemeHovered();
	if (USoundBase* SoundBase = Cast<USoundBase>(WidgetTheme->ThematicUIThemeData.HoveredTheme.Sound.GetResourceObject()))
		PlaySound(SoundBase);
}

void UThematicUIInteractable::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusLost(InFocusEvent);
	
	SetThemeNormal();
}

void UThematicUIInteractable::SetThemeNormal()
{
	UE_LOGFMT(LogThematicUI, Log, "{Name} is setting theme to normal settings", GetName());
}

void UThematicUIInteractable::SetThemeHovered()
{
	UE_LOGFMT(LogThematicUI, Log, "{Name} is setting theme to hovered settings", GetName());
}

void UThematicUIInteractable::SetThemePressed()
{
	UE_LOGFMT(LogThematicUI, Log, "{Name} is setting theme to pressed settings", GetName());
}

const FThematicUIThemeData& UThematicUIInteractable::GetActualThemeData() const
{
	return ActualThemeData;
}
