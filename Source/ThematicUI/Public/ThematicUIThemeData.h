// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ThematicUIThemeData.generated.h"

USTRUCT(BlueprintType)
struct FThematicUITheme
{
	GENERATED_BODY()
	
	/* Image Data */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FSlateBrush Image;
	
	/* Image Size */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FVector2D ImageSize;
	
	/* Whole Image Tint */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FLinearColor Tint;
	
	/* Fill Color (Only for bar widgets) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FLinearColor FillColor;
	
	/* Draw Type */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	ESlateBrushDrawType::Type DrawType;
	
	/* Outline Settings (As Needed) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FSlateBrushOutlineSettings OutlineSettings;
	
	/* Text Color */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FLinearColor TextColor;
	
	/* Text Font */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FSlateFontInfo TextFont;
	
	/* Sound (For Hovered and Pressed) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	TObjectPtr<USoundBase> Sound;
};

/**
 * 
 */
UCLASS()
class THEMATICUI_API UThematicUIThemeData : public UPrimaryDataAsset
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
