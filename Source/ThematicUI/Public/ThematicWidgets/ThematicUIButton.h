// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThematicWidgets/ThematicUIInteractable.h"
#include "ThematicUIButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTUiButtonPressedDelegate);

/**
 * 
 */
UCLASS()
class THEMATICUI_API UThematicUIButton : public UThematicUIInteractable
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(BindWidget))
	TObjectPtr<class USizeBox> SizeBox;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(BindWidget))
	TObjectPtr<class UButton> Button;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(BindWidget))
	TObjectPtr<class UTextBlock> TextBlock;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
	FVector2D SizeBoxSize = FVector2D(250.0f, 50.0f);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
	FText Text;
	
	UPROPERTY(BlueprintAssignable, Category = "ThematicUI")
	FTUiButtonPressedDelegate TUiButtonPressedDelegate;

protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
	
	virtual void SetThemeNormal() override;
	
	virtual void SetThemeHovered() override;
	
	virtual void SetThemePressed() override;
	
	UFUNCTION()
	void HandleButtonPressed();
	
	UFUNCTION()
	void HandleButtonReleased();
};
