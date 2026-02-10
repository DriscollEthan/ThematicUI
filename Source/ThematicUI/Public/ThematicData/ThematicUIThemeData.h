// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Styling/SlateBrush.h"
#include "ThematicUIThemeData.generated.h"

USTRUCT(BlueprintType)
struct FThematicUITheme
{
	GENERATED_BODY()
	
	/* Image Data */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FSlateBrush Image = FSlateBrush();
	
	/* Fill Color (Only for bar widgets) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FLinearColor FillColor = FLinearColor::White;
	
	/* Text Color */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FLinearColor TextColor = FLinearColor::Black;
	
	/* Text Font */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FSlateFontInfo TextFont = FSlateFontInfo();
	
	/* Sound (For Hovered and Pressed) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	FSlateSound Sound = FSlateSound();
};

/**
 * 
 */
UCLASS()
class THEMATICUI_API UThematicUIThemeData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
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
