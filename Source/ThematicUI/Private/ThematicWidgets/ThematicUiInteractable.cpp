// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/ThematicUiInteractable.h"

#include <Misc/DataValidation.h>

#include "Logging/MessageLog.h"
#include "Misc/UObjectToken.h"

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
	
	if (OldSizeBox)
	{
		OldSizeBox->SetWidthOverride(PrimaryWidgetData.SizeBoxSize.X);
		OldSizeBox->SetHeightOverride(PrimaryWidgetData.SizeBoxSize.Y);
	}
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
	
	if (OldSizeBox)
	{
		OldSizeBox->SetWidthOverride(PrimaryWidgetData.SizeBoxSize.X);
		OldSizeBox->SetHeightOverride(PrimaryWidgetData.SizeBoxSize.Y);
	}
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
	
	if (OldSizeBox)
	{
		OldSizeBox->SetWidthOverride(GetSizeBoxSize().X * GetSizeBoxHoveredSizeMultiplier().X);
		OldSizeBox->SetHeightOverride(GetSizeBoxSize().Y * GetSizeBoxHoveredSizeMultiplier().Y);
	}
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
	
	if (OldSizeBox)
	{
		OldSizeBox->SetWidthOverride(GetSizeBoxSize().X * GetSizeBoxPressedSizeMultiplier().X);
		OldSizeBox->SetHeightOverride(GetSizeBoxSize().Y * GetSizeBoxPressedSizeMultiplier().Y);
	}
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

void UThematicUiInteractable::AddWidgetToSizeBox(UWidget* WidgetToAdd)
{
	//@todo Replace With proper SizeBox when OldSizeBox is Fully Removed
	
	if (!OldSizeBox) { return; }
	
	if (OldSizeBox->HasAnyChildren()) 
	{
		UE_LOGFMT(LogThematicUI, Warning, "{Name}: Attemping to add child to SizeBox. But SizeBox already has a child.", GetName());
	}

	OldSizeBox->AddChild(WidgetToAdd);
}

bool UThematicUiInteractable::Initialize()
{
	const bool bInitializedThisCall = Super::Initialize();

	if (bInitializedThisCall)
	{
		//SizeBox = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass(), FName(TEXT("SizeBox")));
		//WidgetTree->RootWidget = SizeBox;
	}
	
	return bInitializedThisCall;
	
	/* 
	const bool bInitializedThisCall = Super::Initialize();

	if (bInitializedThisCall)
	{
		
	}
	
	return bInitializedThisCall;
	*/
}

void UThematicUiInteractable::SetThemeNormal()
{
	UE_LOGFMT(LogThematicUI, Log, "{Name} is setting theme to normal settings", GetName());
	
	CurrentTheme = ETuiCurrentTheme::Default;
	
	if (OldSizeBox)
	{
		OldSizeBox->SetWidthOverride(GetSizeBoxSize().X);
		OldSizeBox->SetHeightOverride(GetSizeBoxSize().Y);
	}
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
	
	CurrentTheme = ETuiCurrentTheme::Hovered;
	
	if (OldSizeBox)
	{
		OldSizeBox->SetWidthOverride(GetSizeBoxSize().X * GetSizeBoxHoveredSizeMultiplier().X);
		OldSizeBox->SetHeightOverride(GetSizeBoxSize().Y * GetSizeBoxHoveredSizeMultiplier().Y);
	}
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
	
	CurrentTheme = ETuiCurrentTheme::Pressed;
	
	if (OldSizeBox)
	{
		OldSizeBox->SetWidthOverride(GetSizeBoxSize().X * GetSizeBoxPressedSizeMultiplier().X);
		OldSizeBox->SetHeightOverride(GetSizeBoxSize().Y * GetSizeBoxPressedSizeMultiplier().Y);
	}
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(GetSizeBoxSize().X * GetSizeBoxPressedSizeMultiplier().X);
		SizeBox->SetHeightOverride(GetSizeBoxSize().Y * GetSizeBoxPressedSizeMultiplier().Y);
	}
	
	OnTuiInteractableSetToPressedTheme.Broadcast(this);
}

void UThematicUiInteractable::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	SetIsFocusable(true);
	
	if (OldSizeBox)
	{
		OldSizeBox->SetWidthOverride(GetSizeBoxSize().X);
		OldSizeBox->SetHeightOverride(GetSizeBoxSize().Y);
	}
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(GetSizeBoxSize().X);
		SizeBox->SetHeightOverride(GetSizeBoxSize().Y);
	}
	
	CalculateAndSetActualWidgetThemeData();
	
	SetThemeNormal();
}

void UThematicUiInteractable::NativeConstruct()
{
	Super::NativeConstruct();
	
	BindTriggeringInputActionToClick();
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