// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



// Includes
	// Compiler Includes
	#include "CoreMinimal.h"

	// Engine Library Includes


	// Project Library Includes
	

	// Class Specific Includes
	#include "ThematicUiInteractable.h"


// UE Generated Includes
	#include "UThematicUiRadialSlider.generated.h"


// Class Details
	// Forward Declarations 
	
	
	// Delegate Declarations 
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTuiSliderValueChangedDelegate, float, NewValue);
	
	// Helper Enums 
	
	
	// Helper Structs 

/**
 * 
 */
UCLASS(HideDropdown, NotPlaceable, Abstract, Category = "ThematicUi", PrioritizeCategories("ThematicUi"))
class THEMATICUI_API UUThematicUiRadialSlider : public UThematicUiInteractable
{
	GENERATED_BODY()

	// Variables 
	public:


	protected:
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Getter, Category = "ThematicUi|Slider")
	float CurrentValue = 0.5f;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadWrite, Getter, Setter, Category = "ThematicUi|Slider")
	FVector2D ValueRange = FVector2D(0.0f, 1.0f);
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadWrite, Getter, Setter, Category = "ThematicUi|Slider")
	float StepAmount = 0.1f;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUi|Slider")
	FVector2D StartAndEndAngles = {30.0f, 150.0f};
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUi|Slider")
	float BarThickness = 5.0f;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUi|Slider")
	bool bShowSliderThumb = true;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUi|Slider")
	bool bShowSliderHandle = false;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUi|Slider")
	FSlateBrush ThumbImage;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUi|Slider")
	FSlateColor SliderHandleColor;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUi|Slider")
	float RadialSliderPadding = 0.0f;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUi|Image")
	FMargin ImagePadding = 4.0f;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUi|Image")
	TEnumAsByte<EHorizontalAlignment> TextHorizontalAlignment = HAlign_Center;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUi|Image")
	TEnumAsByte<EVerticalAlignment> TextVerticalAlignment = VAlign_Center;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Setter, Category = "ThematicUi|Text", meta = (MultiLine = "true"))
	FText Text;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUi|Text")
	bool bAlwaysDisplayValue;
	
	/* X = Left Padding, Y = Top Padding, Z = Right Padding, W = Bottom Padding */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUi|Text")
	FMargin TextPadding = 0.0f;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadWrite, Category = "ThematicUi|Text")
	bool bShowValueAsPercentage = false;
	
	UPROPERTY(BlueprintAssignable, Category = "ThematicUi")
	FTuiSliderValueChangedDelegate TUiValueChanged;

	private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUi", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UImage> Image;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUi", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class URadialSlider> RadialSlider;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUi", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UTextBlock> TextBlock;

	
// Class Functions
	public:
	/* Getters and Setters */
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const float GetCurrentValue() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetCurrentValue(float NewCurrentValue);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const FVector2D& GetValueRange() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetValueRange(const FVector2D& NewValueRange);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const float GetStepAmount() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetStepAmount(float NewStepAmount);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const FVector2D& GetStartAndEndAngles() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetStartAndEndAngles(const FVector2D& NewStartAndEndAngles);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const float GetBarThickness() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetBarThickness(float NewBarThickness);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const bool GetbShowSliderThumb() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetbShowSliderThumb(bool bNewShowSliderThumb);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const bool GetbShowSliderHandle() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetbShowSliderHandle(bool bNewShowSliderHandle);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const FSlateBrush& GetThumbImage() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetThumbImage(const FSlateBrush& NewThumbImage);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const FSlateColor& GetSliderHandleColor() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetSliderHandleColor(const FSlateColor& NewSliderHandleColor);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const float GetRadialSliderPadding() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetRadialSliderPadding(float NewRadialSliderPadding);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const FMargin& GetImagePadding() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetImagePadding(const FMargin& NewImagePadding);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const EHorizontalAlignment GetTextHorizontalAlignment() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetTextHorizontalAlignment(const EHorizontalAlignment& NewTextHorizontalAlignment);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const EVerticalAlignment GetTextVerticalAlignment() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetTextVerticalAlignment(const EVerticalAlignment& NewTextVerticalAlignment);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const FText& GetText() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetText(const FText& NewText);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const bool GetbAlwaysDisplayValue() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetbAlwaysDisplayValue(bool bNewAlwaysDisplayValue);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const FMargin& GetTextPadding() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetTextPadding(const FMargin& NewTextPadding);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const bool GetbShowValueAsPercentage() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetbShowValueAsPercentage(const bool NewbShowValueAsPercentage);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const float GetPercentage() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi", meta = (BlueprintProtected = "true"))
	const float CalculateCurrentValue(const float Percentage) const;

	protected:
	UFUNCTION(BlueprintCallable, Category = "ThematicUi", meta = (BlueprintProtected = "true"))
	void HandleFloatValueChanged(const float NewValue);
	
	UFUNCTION()
	void HandleControllerFocus();
	
	UFUNCTION()
	void HandleControllerUnFocused();

	private:
	

// Virtual Functions
	public:
	//virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
	
	virtual void SetThemeNormal() override;
	
	virtual void SetThemeHovered() override;
	
	virtual void SetThemePressed() override;

	protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
	
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

	private:
	

};
