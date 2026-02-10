// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThematicUIInteractable.h"
#include "Widgets/Notifications/SProgressBar.h"
#include "UThematicUISlider.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTUiSliderValueChangedDelegate);

/**
 * 
 */
UCLASS()
class THEMATICUI_API UUThematicUISlider : public UThematicUIInteractable
{
	GENERATED_BODY()
	
private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class USizeBox> SizeBox;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UTextBlock> TextBlock;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UProgressBar> ProgressBar;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class USlider> Slider;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "ThematicUI")
	FVector2D ValueRange = FVector2D(0.0f, 1.0f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "ThematicUI")
	float StepAmount = 0.1f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Getter, Category = "ThematicUI")
	float CurrentValue = 0.5f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
	FVector2D SizeBoxSize = FVector2D(250.0f, 50.0f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "ThematicUI")
	FVector2D ThumbSize = FVector2D(8.0f, 80.0f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "ThematicUI")
	FText Text = FText::FromString("Hello");
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	bool bAlwaysShowValue = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	bool bIsHorizontal = true;
	
	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "ThematicUI")
	FTUiSliderValueChangedDelegate TUiOnValueChanged;
	
protected:
	// Overrides To Add Custom Functionality Ontop of Base Functionality
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
	
	virtual void SetThemeNormal() override;
	
	virtual void SetThemeHovered() override;
	
	virtual void SetThemePressed() override;

	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	
protected:
	// Custom Functionality
	UFUNCTION(BlueprintCallable, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	void SetValueRange(const FVector2D& NewValueRange);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	void SetThumbSize(const FVector2D& NewThumbSize);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	void SetText(const FText& NewText);
		
	UFUNCTION(BlueprintPure, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	FVector2D GetValueRange() const;
	
	UFUNCTION(BlueprintPure, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	FVector2D GetThumbSize() const;
	
	UFUNCTION(BlueprintPure, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	FText GetText() const;
	
	UFUNCTION(BlueprintPure, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	float GetCurrentValue() const;
	
	UFUNCTION(BlueprintPure, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	float GetStepAmount() const;
	
	UFUNCTION(BlueprintPure, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	float GetPercentage() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	void SetStepAmount(const float NewStepAmount);
	
	UFUNCTION(BlueprintPure, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	float CalculateCurrentValue(const float Percentage) const;
	
	UFUNCTION(BlueprintPure, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
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
