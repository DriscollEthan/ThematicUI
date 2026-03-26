#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateBrush.h"
#include "Sound/SlateSound.h"
#include "Fonts/SlateFontInfo.h"
#include "ThematicUIData.generated.h"

USTRUCT(BlueprintType)
struct FThematicUITheme
{
	GENERATED_BODY()
	
	/* Image Data */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FSlateBrush Image;
	
	/* Fill Color (Only for bar widgets) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FLinearColor FillColor = FLinearColor::White;
	
	/* Text Color */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FLinearColor TextColor = FLinearColor::Black;
	
	/* Text Font */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FSlateFontInfo TextFont;
	
	/* Sound (For Hovered and Pressed) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FSlateSound Sound;
};

USTRUCT(BlueprintType)
struct FThematicUIThemeData
{
	GENERATED_BODY()
	
	/* Normal Theme */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FThematicUITheme NormalTheme;
	
	/* Hovered Theme */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FThematicUITheme HoveredTheme;
	
	/* Pressed Theme */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FThematicUITheme PressedTheme;
};

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
	
	FThematicUITheme ConvertToTheme(const FThematicUITheme& InTheme) const
	{
		FThematicUITheme Theme;
		
		Theme.Image = (bOverrideImage) ? Image : InTheme.Image;
		Theme.FillColor = (bOverrideFillColor) ? FillColor : InTheme.FillColor;
		Theme.TextColor = (bOverrideTextColor) ? TextColor : InTheme.TextColor;
		Theme.TextFont = (bOverrideTextFont) ? TextFont : InTheme.TextFont;
		Theme.Sound = (bOverrideSound) ? Sound : InTheme.Sound;
		
		return Theme;
	}
	
	FThematicUITheme ConvertToTheme(const FThematicUIThemeOverride& InTheme) const
	{
		FThematicUITheme Theme;
		
		Theme.Image = (bOverrideImage) ? Image : InTheme.Image;
		Theme.FillColor = (bOverrideFillColor) ? FillColor : InTheme.FillColor;
		Theme.TextColor = (bOverrideTextColor) ? TextColor : InTheme.TextColor;
		Theme.TextFont = (bOverrideTextFont) ? TextFont : InTheme.TextFont;
		Theme.Sound = (bOverrideSound) ? Sound : InTheme.Sound;
		
		return Theme;
	}
	
	const FThematicUIThemeOverride& ConvertFromTheme(const FThematicUITheme& InTheme)
	{
		Image = (bOverrideImage) ? Image : InTheme.Image;
		FillColor = (bOverrideFillColor) ? FillColor : InTheme.FillColor;
		TextColor = (bOverrideTextColor) ? TextColor : InTheme.TextColor;
		TextFont = (bOverrideTextFont) ? TextFont : InTheme.TextFont;
		Sound = (bOverrideSound) ? Sound : InTheme.Sound;
		
		return *this;
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
	
	FThematicUIThemeData ConvertToThemeData(const FThematicUIThemeData& InThemeData) const
	{
		FThematicUIThemeData ThemeData;
		
		ThemeData.NormalTheme = NormalThemeOverride.ConvertToTheme(InThemeData.NormalTheme);
		ThemeData.HoveredTheme = HoveredThemeOverride.ConvertToTheme(InThemeData.HoveredTheme);
		ThemeData.PressedTheme = PressedThemeOverride.ConvertToTheme(InThemeData.PressedTheme);
		
		return ThemeData;
	}
	
	FThematicUIThemeData ConvertToThemeData(const FThematicUIThemeDataOverride& InThemeData) const
	{
		FThematicUIThemeData ThemeData;
		
		ThemeData.NormalTheme = NormalThemeOverride.ConvertToTheme(InThemeData.NormalThemeOverride);
		ThemeData.HoveredTheme = HoveredThemeOverride.ConvertToTheme(InThemeData.HoveredThemeOverride);
		ThemeData.PressedTheme = PressedThemeOverride.ConvertToTheme(InThemeData.PressedThemeOverride);
		
		return ThemeData;
	}
	
	const FThematicUIThemeDataOverride& ConvertFromThemeData(const FThematicUIThemeData& InThemeData)
	{
		NormalThemeOverride.ConvertFromTheme(InThemeData.NormalTheme);
		HoveredThemeOverride.ConvertFromTheme(InThemeData.HoveredTheme);
		PressedThemeOverride.ConvertFromTheme(InThemeData.PressedTheme);
		
		return *this;
	}
};