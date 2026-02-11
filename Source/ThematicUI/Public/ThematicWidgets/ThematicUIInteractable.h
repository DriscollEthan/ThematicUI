// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Logging/StructuredLog.h"
#include "ThematicData/ThematicUIThemeData.h"
#include "ThematicUIInteractable.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogThematicUI, Log, All)

/**
 * 
 */
UCLASS()
class THEMATICUI_API UThematicUIInteractable : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	/* Widget Theme Data */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI", meta = (DisplayPriority = 1))
	TObjectPtr<UThematicUIThemeData> WidgetTheme;
	
protected:
	/**
	 * NativeConstruct is to set active theme to NormalTheme 
	 */
	virtual void NativeConstruct() override;
	
	/**
	 * This will ensure user focus gets set to this widget on MouseHover
	 * @param InGeometry 
	 * @param InMouseEvent 
	 */
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	/**
	 * NativeOnAddedToFocusPath is Called when Widget gains User Focus
	 * @param InFocusEvent 
	 */
	virtual void NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent) override;
	
	/**
	 *  NativeOnFocusLost is Called when Widget gains User Focus
	 * @param InFocusEvent 
	 */
	virtual void NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent) override;
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI | SetTheme")
	virtual void SetThemeNormal();
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI | SetTheme")
	virtual void SetThemeHovered();
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI | SetTheme")
	virtual void SetThemePressed();
};
