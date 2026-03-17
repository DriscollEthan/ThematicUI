// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Styling/SlateBrush.h"
#include "Sound/SlateSound.h"
#include "Fonts/SlateFontInfo.h"
#include "ThematicUIThemeData.generated.h"

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

/**
 * 
 */
UCLASS()
class THEMATICUI_API UThematicUIThemeDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FThematicUIThemeData ThematicUIThemeData;
};
