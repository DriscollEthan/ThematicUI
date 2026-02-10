// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThematicUIInteractable.h"
#include "UThematicUIRadialSlider.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTuiSliderValueChangedDelegate);

/**
 * 
 */
UCLASS()
class THEMATICUI_API UUThematicUIRadialSlider : public UThematicUIInteractable
{
	GENERATED_BODY()
	
private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class USizeBox> SizeBox;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UImage> Image;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class URadialSlider> RadialSlider;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UTextBlock> TextBlock;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "ThematicUI")
	FVector2D ValueRange = FVector2D(0.0f, 1.0f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "ThematicUI")
	float StepAmount = 0.1f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter, Category = "ThematicUI")
	float CurrentValue = 0.5f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
	FVector2D SizeBoxSize = {250.0f, 250.0f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
	float RadialSliderPadding = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
	FSlateBrush ThumbImage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
	FVector2D StartAndEndAngles = {30.0f, 150.0f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
	bool bShowSliderThumb = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
	bool bShowSliderHandle = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
	FMargin ImagePadding = 4.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
	TEnumAsByte<EHorizontalAlignment> TextHorizontalAlignment = HAlign_Center;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
	TEnumAsByte<EVerticalAlignment> TextVerticalAlignment = VAlign_Center;
	
	/* X = Left Padding, Y = Top Padding, Z = Right Padding, W = Bottom Padding */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
	FMargin TextPadding = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Setter, Category = "ThematicUI")
	FText Text;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
	bool bAlwaysDisplayValue;
	
	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "ThematicUI")
	FTuiSliderValueChangedDelegate TUiValueChanged;
	
protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
	
	virtual void SetThemeNormal() override;
	
	virtual void SetThemeHovered() override;
	
	virtual void SetThemePressed() override;
	
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	
protected:
	UFUNCTION(BlueprintCallable, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	FVector2D GetValueRange() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	void SetValueRange(const FVector2D& NewValueRange);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	float GetStepAmount() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	void SetStepAmount(const float NewStepAmount);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	float GetCurrentValue() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	void SetText(const FText& NewText);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	float GetPercentage() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	float CalculateCurrentValue(const float Percentage) const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	float UpdateSteppingSize() const;
	
protected:
	// Handle Dispatchers
	UFUNCTION(BlueprintCallable, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	void HandleFloatValueChanged(const float NewValue);
	
	UFUNCTION()
	void HandleControllerFocus();
	
	UFUNCTION()
	void HandleControllerUnFocused();
};
