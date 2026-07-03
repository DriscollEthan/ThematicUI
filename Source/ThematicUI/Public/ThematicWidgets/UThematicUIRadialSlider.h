// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



// Includes
	// Compiler Includes
	#include "CoreMinimal.h"

	// Engine Library Includes


	// Project Library Includes
	

	// Class Specific Includes
	#include "ThematicUIInteractable.h"


	// UE Generated Includes
	#include "UThematicUIRadialSlider.generated.h"


// Class Details
	// Forward Declarations 
	
	
	// Delegate Declarations 
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTuiSliderValueChangedDelegate, float, NewValue);
	
	// Helper Enums 
	
	
	// Helper Structs 

/**
 * 
 */
UCLASS(HideDropdown, NotPlaceable)
class THEMATICUI_API UUThematicUIRadialSlider : public UThematicUIInteractable
{
	GENERATED_BODY()

	// Variables 
	public:


	protected:
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
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadWrite, Category = "ThematicUI|Text")
	bool bShowValueAsPercentage = false;
	
	UPROPERTY(BlueprintAssignable, Category = "ThematicUI")
	FTuiSliderValueChangedDelegate TUiValueChanged;

	private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UImage> Image;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class URadialSlider> RadialSlider;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UTextBlock> TextBlock;

	
// Class Functions
	public:
	/* Getters and Setters */
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const float GetCurrentValue() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetCurrentValue(float NewCurrentValue);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const FVector2D& GetValueRange() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetValueRange(const FVector2D& NewValueRange);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const float GetStepAmount() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetStepAmount(float NewStepAmount);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const FVector2D& GetStartAndEndAngles() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetStartAndEndAngles(const FVector2D& NewStartAndEndAngles);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const float GetBarThickness() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetBarThickness(float NewBarThickness);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const bool GetbShowSliderThumb() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetbShowSliderThumb(bool bNewShowSliderThumb);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const bool GetbShowSliderHandle() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetbShowSliderHandle(bool bNewShowSliderHandle);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const FSlateBrush& GetThumbImage() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetThumbImage(const FSlateBrush& NewThumbImage);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const float GetRadialSliderPadding() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetRadialSliderPadding(float NewRadialSliderPadding);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const FMargin& GetImagePadding() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetImagePadding(const FMargin& NewImagePadding);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const EHorizontalAlignment GetTextHorizontalAlignment() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetTextHorizontalAlignment(const EHorizontalAlignment& NewTextHorizontalAlignment);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const EVerticalAlignment GetTextVerticalAlignment() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetTextVerticalAlignment(const EVerticalAlignment& NewTextVerticalAlignment);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const FText& GetText() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetText(const FText& NewText);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const bool GetbAlwaysDisplayValue() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetbAlwaysDisplayValue(bool bNewAlwaysDisplayValue);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const FMargin& GetTextPadding() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetTextPadding(const FMargin& NewTextPadding);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const bool GetbShowValueAsPercentage() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetbShowValueAsPercentage(const bool NewbShowValueAsPercentage);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const float GetPercentage() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	const float CalculateCurrentValue(const float Percentage) const;

	protected:
	UFUNCTION(BlueprintCallable, Category = "ThematicUI", meta = (BlueprintProtected = "true"))
	void HandleFloatValueChanged(const float NewValue);
	
	UFUNCTION()
	void HandleControllerFocus();
	
	UFUNCTION()
	void HandleControllerUnFocused();

	private:



// Project Class Virtual Functions
	public:
	virtual void SetThemeNormal() override;
	
	virtual void SetThemeHovered() override;
	
	virtual void SetThemePressed() override;

	protected:
	

	private:
	


// Unreal Class Virtual Functions
	public:


	protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
	
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

	private:
	

};
