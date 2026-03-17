// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThematicUIInteractable.h"
#include "ThematicUITextBlock.generated.h"

/**
 * 
 */
UCLASS(HideDropdown, NotPlaceable)
class THEMATICUI_API UThematicUITextBlock : public UThematicUIInteractable
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class USizeBox> SizeBox;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UBorder> Border;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UTextBlock> TextBlock;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
	FVector2D SizeBoxSize = FVector2D(250.0f, 50.0f);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Setter, Category = "ThematicUI", meta = (MultiLine = "true"))
	FText Text;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
	float LineHeightPercentage = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
	TEnumAsByte<ETextJustify::Type> Justification = ETextJustify::Left;
	
	
protected:
	UFUNCTION(BlueprintCallable, Category = "ThematicUI")
	void SetText(FText NewText);
	
protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
	
	virtual void SetThemeNormal() override;
	
	virtual void SetThemeHovered() override;
	
	virtual void SetThemePressed() override;
};
