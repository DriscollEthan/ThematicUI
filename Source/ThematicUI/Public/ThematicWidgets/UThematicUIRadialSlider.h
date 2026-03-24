// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThematicUIInteractable.h"
#include "UThematicUIRadialSlider.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTuiSliderValueChangedDelegate, float, NewValue);

/**
 * 
 */
UCLASS(HideDropdown, NotPlaceable)
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
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI")
	FVector2D SizeBoxSize = {250.0f, 250.0f};	
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Getter, Category = "ThematicUI|Slider")
	float CurrentValue = 0.5f;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadWrite, Getter, Setter, Category = "ThematicUI|Slider")
	FVector2D ValueRange = FVector2D(0.0f, 1.0f);
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadWrite, Getter, Setter, Category = "ThematicUI|Slider")
	float StepAmount = 0.1f;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI|Slider")
	FVector2D StartAndEndAngles = {30.0f, 150.0f};
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI|Slider")
	float BarThickness = 5.0f;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI|Slider")
	bool bShowSliderThumb = true;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI|Slider")
	bool bShowSliderHandle = false;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI|Slider")
	FSlateBrush ThumbImage;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI|Slider")
	float RadialSliderPadding = 0.0f;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI|Image")
	FMargin ImagePadding = 4.0f;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI|Image")
	TEnumAsByte<EHorizontalAlignment> TextHorizontalAlignment = HAlign_Center;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI|Image")
	TEnumAsByte<EVerticalAlignment> TextVerticalAlignment = VAlign_Center;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Setter, Category = "ThematicUI|Text", meta = (MultiLine = "true"))
	FText Text;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI|Text")
	bool bAlwaysDisplayValue;
	
	/* X = Left Padding, Y = Top Padding, Z = Right Padding, W = Bottom Padding */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI|Text")
	FMargin TextPadding = 0.0f;
	
	UPROPERTY(BlueprintAssignable, Category = "ThematicUI")
	FTuiSliderValueChangedDelegate TUiValueChanged;
	
public:
	/* Getters and Setters */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Getters")
	const FVector2D& GetSizeBoxSize() const;
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Setters")
	void SetSizeBoxSize(const FVector2D& NewSizeBoxSize);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Getters")
	const float& GetCurrentValue() const;
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Setters")
	void SetCurrentValue(const float& NewCurrentValue);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Getters")
	const FVector2D& GetValueRange() const;
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Setters")
	void SetValueRange(const FVector2D& NewValueRange);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Getters")
	const float& GetStepAmount() const;
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Setters")
	void SetStepAmount(const float& NewStepAmount);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Getters")
	const FVector2D& GetStartAndEndAngles() const;
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Setters")
	void SetStartAndEndAngles(const FVector2D& NewStartAndEndAngles);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Getters")
	const float& GetBarThickness() const;
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Setters")
	void SetBarThickness(const float& NewBarThickness);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Getters")
	const bool& GetbShowSliderThumb() const;
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Setters")
	void SetbShowSliderThumb(const bool& bNewShowSliderThumb);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Getters")
	const bool& GetbShowSliderHandle() const;
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Setters")
	void SetbShowSliderHandle(const bool& bNewShowSliderHandle);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Getters")
	const FSlateBrush& GetThumbImage() const;
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Setters")
	void SetThumbImage(const FSlateBrush& NewThumbImage);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Getters")
	const float& GetRadialSliderPadding() const;
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Setters")
	void SetRadialSliderPadding(const float& NewRadialSliderPadding);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Getters")
	const FMargin& GetImagePadding() const;
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Setters")
	void SetImagePadding(const FMargin& NewImagePadding);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Getters")
	const EHorizontalAlignment GetTextHorizontalAlignment() const;
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Setters")
	void SetTextHorizontalAlignment(const EHorizontalAlignment& NewTextHorizontalAlignment);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Getters")
	const EVerticalAlignment GetTextVerticalAlignment() const;
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Setters")
	void SetTextVerticalAlignment(const EVerticalAlignment& NewTextVerticalAlignment);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Getters")
	const FText& GetText() const;
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Setters")
	void SetText(const FText& NewText);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Getters")
	const bool& GetbAlwaysDisplayValue() const;
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Setters")
	void SetbAlwaysDisplayValue(const bool& bNewAlwaysDisplayValue);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Getters")
	const FMargin& GetTextPadding() const;
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI|Setters")
	void SetTextPadding(const FMargin& NewTextPadding);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	const float GetPercentage() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	const float CalculateCurrentValue(const float Percentage) const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	const float UpdateSteppingSize() const;

protected:
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
