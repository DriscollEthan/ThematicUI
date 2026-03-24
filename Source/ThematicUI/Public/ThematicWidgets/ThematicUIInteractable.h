// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Logging/StructuredLog.h"
#include "ThematicData/ThematicUIThemeData.h"
#include "ThematicUIInteractable.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogThematicUI, Log, All)


USTRUCT(BlueprintType)
struct FThematicUIThemeOverride
{
	GENERATED_BODY()
	
	/* Image Data */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	bool bOverrideImage = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI", meta = (EditCondition = "bOverrideImage"))
	FSlateBrush Image;
	
	/* Fill Color (Only for bar widgets) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	bool bOverrideFillColor = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI", meta = (EditCondition = "bOverrideFillColor"))
	FLinearColor FillColor = FLinearColor::White;
	
	/* Text Color */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	bool bOverrideTextColor = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI", meta = (EditCondition = "bOverrideTextColor"))
	FLinearColor TextColor = FLinearColor::Black;
	
	/* Text Font */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	bool bOverrideTextFont = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI", meta = (EditCondition = "bOverrideTextFont"))
	FSlateFontInfo TextFont;
	
	/* Sound (For Hovered and Pressed) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	bool bOverrideSound = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI", meta = (EditCondition = "bOverrideSound"))
	FSlateSound Sound;
	
	FThematicUITheme ConvertToTheme() const
	{
		FThematicUITheme Theme;
		
		Theme.Image = Image;
		Theme.FillColor = FillColor;
		Theme.TextColor = TextColor;
		Theme.TextFont = TextFont;
		Theme.Sound = Sound;
		
		return Theme;
	}
	
	FThematicUITheme ConvertToTheme(FThematicUITheme InTheme) const
	{
		FThematicUITheme Theme;
		
		Theme.Image = (bOverrideImage) ? Image : InTheme.Image;
		Theme.FillColor = (bOverrideFillColor) ? FillColor : InTheme.FillColor;
		Theme.TextColor = (bOverrideTextColor) ? TextColor : InTheme.TextColor;
		Theme.TextFont = (bOverrideTextFont) ? TextFont : InTheme.TextFont;
		Theme.Sound = (bOverrideSound) ? Sound : InTheme.Sound;
		
		return Theme;
	}
};

USTRUCT(BlueprintType)
struct FThematicUIThemeDataOverride
{
	GENERATED_BODY()
	
	/* Normal Theme */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FThematicUIThemeOverride NormalThemeOverride;
	
	/* Hovered Theme */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FThematicUIThemeOverride HoveredThemeOverride;
	
	/* Pressed Theme */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FThematicUIThemeOverride PressedThemeOverride;
	
	FThematicUIThemeData ConvertToThemeData() const
	{
		FThematicUIThemeData ThemeData;
		
		ThemeData.NormalTheme = NormalThemeOverride.ConvertToTheme();
		ThemeData.HoveredTheme = HoveredThemeOverride.ConvertToTheme();
		ThemeData.PressedTheme = PressedThemeOverride.ConvertToTheme();
		
		return ThemeData;
	}
	
	FThematicUIThemeData ConvertToThemeData(const UThematicUIThemeDataAsset* InThemeDataAsset) const
	{
		FThematicUIThemeData ThemeData;
		
		ThemeData.NormalTheme = NormalThemeOverride.ConvertToTheme(InThemeDataAsset->ThematicUIThemeData.NormalTheme);
		ThemeData.HoveredTheme = HoveredThemeOverride.ConvertToTheme(InThemeDataAsset->ThematicUIThemeData.HoveredTheme);
		ThemeData.PressedTheme = PressedThemeOverride.ConvertToTheme(InThemeDataAsset->ThematicUIThemeData.PressedTheme);
		
		return ThemeData;
	}
};

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
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Getters")
	const FThematicUIThemeDataOverride& GetWidgetThemeOverrideData() const;
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Setters")
	void SetWidgetThemeOverrideData(const FThematicUIThemeDataOverride& NewWidgetTHemeOverrideData);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Getters")
	const FThematicUIThemeData& GetActualThemeData() const;
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Setters")
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
