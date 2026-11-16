// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/ThematicUiButton.h"

#include <DetailCategoryBuilder.h>
#include <Blueprint/WidgetTree.h>
#include <Components/SizeBox.h>

#include "Components/Button.h"
#include "Components/TextBlock.h"

const FText& UThematicUiButton::GetText() const
{
	return Text;
}

void UThematicUiButton::SetText(const FText& value)
{
	Text = value;
	
	if (TextBlock)
	{
		TextBlock->SetText(Text);
	}
}

bool UThematicUiButton::TuiHasUserFocus()
{
	return CommonButton->HasAnyUserFocus();
}

void UThematicUiButton::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (TextBlock)
	{
		TextBlock->SetText(Text);
	}
}

void UThematicUiButton::NativeConstruct()
{
	Super::NativeConstruct();
	
	CommonButton->OnPressed.AddUniqueDynamic(this, &ThisClass::HandleButtonPressed);
	CommonButton->OnReleased.AddUniqueDynamic(this, &ThisClass::HandleButtonReleased);
	CommonButton->SetButtonEnabled(true);
	CommonButton->SetButtonFocusable(true);
	CommonButton->SetPressMethod(EButtonPressMethod::Type::ButtonPress);
}

FReply UThematicUiButton::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	if (CommonButton)
	{
		return FReply::Handled().SetUserFocus(CommonButton->TakeWidget(), InFocusEvent.GetCause());
	}

	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

void UThematicUiButton::SetThemeNormal()
{
	Super::SetThemeNormal();
	
	if (CommonButton && TextBlock) [[likely]]
	{
		// Create Button Style to Change
		FButtonStyle Style;

		// Set Image Settings / SlateBrush
		Style.SetNormal(ActualThemeData.NormalTheme.Image);
		Style.SetHovered(ActualThemeData.NormalTheme.Image);
		Style.SetPressed(ActualThemeData.NormalTheme.Image);
	
		// Set Sounds
		Style.SetHoveredSound(ActualThemeData.HoveredTheme.Sound);
		Style.SetPressedSound(ActualThemeData.PressedTheme.Sound);
	
		// Set Button Style
		CommonButton->SetStyle(Style);
	
		//Set Text Style
		TextBlock->SetFont(ActualThemeData.NormalTheme.TextFont);
		TextBlock->SetColorAndOpacity(ActualThemeData.NormalTheme.TextColor);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUiButton::SetThemeNormal : UThematicUiButton::Button == nullptr || UThematicUiButton::TextBlock == nullptr");
	}
}

void UThematicUiButton::SetThemeHovered()
{
	Super::SetThemeHovered();
	
	if (CommonButton && TextBlock) [[likely]]
	{
		// Create Button Style to Change
		FButtonStyle Style;

		// Set Image Settings / SlateBrush
		Style.SetNormal(ActualThemeData.HoveredTheme.Image);
		Style.SetHovered(ActualThemeData.HoveredTheme.Image);
		Style.SetPressed(ActualThemeData.HoveredTheme.Image);
	
		// Set Sounds
		Style.SetHoveredSound(ActualThemeData.HoveredTheme.Sound);
		Style.SetPressedSound(ActualThemeData.PressedTheme.Sound);
	
		// Set Button Style
		CommonButton->SetStyle(Style);
	
		//Set Text Style
		TextBlock->SetColorAndOpacity(ActualThemeData.HoveredTheme.TextColor);
		TextBlock->SetFont(ActualThemeData.HoveredTheme.TextFont);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUiButton::SetThemeNormal : UThematicUiButton::Button == nullptr || UThematicUiButton::TextBlock == nullptr");
	}
}

void UThematicUiButton::SetThemePressed()
{
	Super::SetThemePressed();
	
	if (CommonButton && TextBlock) [[likely]]
	{
		// Create Button Style to Change
		FButtonStyle Style;

		// Set Image Settings / SlateBrush
		Style.SetNormal(ActualThemeData.PressedTheme.Image);
		Style.SetHovered(ActualThemeData.PressedTheme.Image);
		Style.SetPressed(ActualThemeData.PressedTheme.Image);
	
		// Set Sounds
		Style.SetHoveredSound(ActualThemeData.HoveredTheme.Sound);
		Style.SetPressedSound(ActualThemeData.PressedTheme.Sound);
	
		// Set Button Style
		CommonButton->SetStyle(Style);
	
		//Set Text Style
		TextBlock->SetColorAndOpacity(ActualThemeData.PressedTheme.TextColor);
		TextBlock->SetFont(ActualThemeData.PressedTheme.TextFont);
	}
	else
	{
		UE_LOGFMT(LogThematicUI, Error, "UThematicUiButton::SetThemeNormal : UThematicUiButton::Button == nullptr || UThematicUiButton::TextBlock == nullptr");
	}
}

void UThematicUiButton::HandleButtonPressed()
{
	if (CommonButton->HasFocusedDescendants())
	{
		SetThemePressed();
		
		OnTuiButtonPressedDelegate.Broadcast(this);
	}
}

void UThematicUiButton::HandleButtonReleased()
{
	if (CommonButton->HasFocusedDescendants())
	{
		SetThemeHovered();
		
		OnTuiButtonReleaseddDelegate.Broadcast(this);
		OnTuiButtonClickedDelegate.Broadcast(this);
	}
}

bool UThematicUiButton::Initialize()
{
	const bool bInitializedThisCall = Super::Initialize();

	if (bInitializedThisCall)
	{
		CommonButton = WidgetTree->ConstructWidget<UCommonButtonInternalBase>(UCommonButtonInternalBase::StaticClass(), FName(TEXT("CommonButton")));
		SizeBox->AddChild(CommonButton);
		TextBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), FName(TEXT("TextBlock")));
		CommonButton->AddChild(TextBlock);
	}

	return bInitializedThisCall;
}
