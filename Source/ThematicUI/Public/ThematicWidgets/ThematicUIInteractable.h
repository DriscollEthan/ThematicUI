// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThematicUI.h"
#include "Blueprint/UserWidget.h"
#include "ThematicData/ThematicUIThemeData.h"
#include "ThematicUIInteractable.generated.h"


/**
 * 
 */
UCLASS(HideDropdown, NotPlaceable)
class THEMATICUI_API UThematicUIInteractable : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	/* Widget Theme Data */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI", meta = (DisplayPriority = 1))
	TObjectPtr<UThematicUIThemeDataAsset> WidgetTheme;
	
	/* Widget Theme Data Override */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "ThematicUI", meta = (DisplayPriority = 1))
	FThematicUIThemeDataOverride WidgetThemeOverrideData;
	
	/* Actual Widget Theme Data */
	UPROPERTY(BlueprintReadOnly, Getter, Category = "ThematicUI")
	FThematicUIThemeData ActualThemeData;
	
public:
	/* Getters and Setters */
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const FThematicUIThemeDataOverride& GetWidgetThemeOverrideData() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetWidgetThemeOverrideData(const FThematicUIThemeDataOverride& NewWidgetTHemeOverrideData);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetWidgetNormalThemeOverrideDate(const FThematicUIThemeOverride& NewWidgetNormalThemeOverride);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetWidgetHoveredThemeOverrideDate(const FThematicUIThemeOverride& NewWidgetHoveredThemeOverride);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetWidgetPressedThemeOverrideDate(const FThematicUIThemeOverride& NewWidgetPressedThemeOverride);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const FThematicUIThemeData& GetActualThemeData() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void CalculateAndSetActualWidgetThemeData();
	
protected:
	/**
	 * NativePreConstruct is to set active theme to NormalTheme and Calculate Actual Theme Data
	 */
	virtual void NativePreConstruct() override;
	
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
