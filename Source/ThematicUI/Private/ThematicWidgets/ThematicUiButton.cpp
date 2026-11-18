// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicWidgets/ThematicUiButton.h"

#include <CommonUITypes.h>
#include <DetailCategoryBuilder.h> 
#include <ICommonInputModule.h>
#include <Input/CommonUIInputTypes.h>

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ThematicModule/ThematicUiSettings.h"

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
	if (TuiHasUserFocus())
	{
		SetThemePressed();
		
		OnTuiButtonPressedDelegate.Broadcast(this);
	}
}

void UThematicUiButton::HandleButtonReleased()
{
	if (TuiHasUserFocus())
	{
		SetThemeHovered();
		
		OnTuiButtonReleasedDelegate.Broadcast(this);
		OnTuiButtonClickedDelegate.Broadcast(this);
	}
}

void UThematicUiButton::BindTriggeringInputActionToClick()
{
	if (CommonUI::IsEnhancedInputSupportEnabled() && TriggeringEnhancedInputAction)
	{
		FBindUIActionArgs BindArgs(TriggeringEnhancedInputAction, false, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleButtonReleased));
		BindArgs.OnExecuteAction.BindUObject(this, &ThisClass::HandleButtonReleased);
		BindArgs.OnHoldActionPressed.BindUObject(this, &ThisClass::HandleButtonPressed);
		BindArgs.OnHoldActionReleased.BindUObject(this, &ThisClass::HandleButtonPressed);
		BindArgs.bIsPersistent = bIsPersistentBinding;
		BindArgs.InputMode = OverrideInputMode;

		TriggeringBindingHandle = RegisterUIActionBinding(BindArgs);
	}
	
	
	
	FDataTableRowHandle defaultTriggerAction = ICommonInputModule::Get().GetSettings().GetDefaultClickAction();
	UInputAction* defaultTriggerInputAction = FThematicUiModule::Get().GetThematicUiSettings()->GetDefaultClickInputAction();
	
	if (defaultTriggerInputAction && ICommonInputModule::Get().GetSettings().GetEnableEnhancedInputSupport())
	{
			FThematicUiModule::BindMappingContext(this);
	
		FBindUIActionArgs BindArgs(defaultTriggerInputAction, false, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleButtonReleased));
		
		BindArgs.OnExecuteAction.BindUObject(this, &ThisClass::HandleButtonReleased);
		BindArgs.OnHoldActionPressed.BindUObject(this, &ThisClass::HandleButtonPressed);
		BindArgs.OnHoldActionReleased.BindUObject(this, &ThisClass::HandleButtonPressed);
		BindArgs.bIsPersistent = bIsPersistentBinding;
		BindArgs.InputMode = OverrideInputMode;
		BindArgs.bIsPersistent = true;

		DefaultTriggeringBindingHandle = RegisterUIActionBinding(BindArgs);
	}
	else if (!defaultTriggerAction.IsNull())
	{
		FBindUIActionArgs BindArgs(defaultTriggerAction, false, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleButtonReleased));
		
		BindArgs.OnExecuteAction.BindUObject(this, &ThisClass::HandleButtonReleased);
		BindArgs.OnHoldActionPressed.BindUObject(this, &ThisClass::HandleButtonPressed);
		BindArgs.OnHoldActionReleased.BindUObject(this, &ThisClass::HandleButtonPressed);
		BindArgs.bIsPersistent = bIsPersistentBinding;
		BindArgs.InputMode = OverrideInputMode;
		BindArgs.bIsPersistent = true;

		DefaultTriggeringBindingHandle = RegisterUIActionBinding(BindArgs);
	}
}

bool UThematicUiButton::Initialize()
{
	const bool bInitializedThisCall = Super::Initialize();

	if (bInitializedThisCall)
	{
		CommonButton = WidgetTree->ConstructWidget<UCommonButtonInternalBase>(UCommonButtonInternalBase::StaticClass(), FName(TEXT("CommonButton")));
		
		AddWidgetToSizeBox(CommonButton);
		CommonButton->SetClickMethod(ClickMethod);
		CommonButton->SetTouchMethod(TouchMethod);
		CommonButton->SetPressMethod(PressMethod);
		CommonButton->SetButtonFocusable(IsFocusable());
		CommonButton->SetButtonEnabled(bButtonEnabled);
		CommonButton->SetInteractionEnabled(bInteractionEnabled);
		
		TextBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), FName(TEXT("TextBlock")));
		CommonButton->AddChild(TextBlock);
	}

	return bInitializedThisCall;
}
