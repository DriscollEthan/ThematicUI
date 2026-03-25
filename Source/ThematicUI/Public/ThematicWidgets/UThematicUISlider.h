// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThematicUIInteractable.h"
#include "Widgets/Notifications/SProgressBar.h"
#include "UThematicUISlider.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTUiSliderValueChangedDelegate, float, NewValue);

/**
 * 
 */
UCLASS(HideDropdown, NotPlaceable)
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
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI")
	FVector2D SizeBoxSize = FVector2D(250.0f, 50.0f);
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Getter, Category = "ThematicUI|Slider")
	float CurrentValue = 0.5f;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadWrite, Getter, Setter, Category = "ThematicUI|Slider")
	FVector2D ValueRange = FVector2D(0.0f, 1.0f);
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadWrite, Getter, Setter, Category = "ThematicUI|Slider")
	float StepAmount = 0.1f;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadWrite, Category = "ThematicUI|Slider")
	bool bIsHorizontal = true;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadWrite, Getter, Setter, Category = "ThematicUI|Slider")
	FVector2D ThumbSize = FVector2D(8.0f, 80.0f);
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadWrite, Getter, Setter, Category = "ThematicUI|Text", meta = (MultiLine = "true"))
	FText Text = FText::FromString("Hello");
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadWrite, Category = "ThematicUI|Text")
	bool bAlwaysShowValue = false;
	
	UPROPERTY(BlueprintAssignable, Category = "ThematicUI")
	FTUiSliderValueChangedDelegate TUiOnValueChanged;
	
public:
	/* Getters and Setters */
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const FVector2D& GetSizeBoxSize() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetSizeBoxSize(const FVector2D& NewSizeBoxSize);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const float GetCurrentValue() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetCurrentValue(const float NewCurrentValue);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	FVector2D GetValueRange() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetValueRange(const FVector2D& NewValueRange);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	float GetStepAmount() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetStepAmount(const float NewStepAmount);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const bool GetbIsHorizontal() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetbIsHorizontal(const bool NewbIsHorizontal);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const FVector2D& GetThumbSize() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetThumbSize(const FVector2D& NewThumbSize);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const FText& GetText() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetText(const FText& NewText);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const bool GetbAlwaysShowValue() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetbAlwaysShowValue(const bool NewbAlwaysShowValue);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const float GetPercentage() const;
	
	UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
	const float CalculateCurrentValue(const float Percentage) const;
	
protected:
	// Overrides To Add Custom Functionality Ontop of Base Functionality
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
	
	virtual void SetThemeNormal() override;
	
	virtual void SetThemeHovered() override;
	
	virtual void SetThemePressed() override;

	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

protected:
	// Handle Dispatchers
	UFUNCTION(BlueprintCallable, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	void HandleFloatValueChanged(const float NewValue);
	
	UFUNCTION()
	void HandleControllerFocus();
	
	UFUNCTION()
	void HandleControllerUnFocused();
};
