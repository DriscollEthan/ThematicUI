// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



// Includes
	// Compiler Includes
	#include "CoreMinimal.h"

	// Engine Library Includes
#include "Widgets/Notifications/SProgressBar.h"

	// Project Library Includes
	

	// Class Specific Includes
	#include "ThematicUiInteractable.h"

// UE Generated Includes
	#include "UThematicUiSlider.generated.h"


// Class Details
	// Forward Declarations 
	
	
	// Delegate Declarations 
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTUiSliderValueChangedDelegate, float, NewValue);
	
	// Helper Enums 
	
	
	// Helper Structs 

/**
 * 
 */
UCLASS(HideDropdown, NotPlaceable, Abstract, Category = "ThematicUi")
class THEMATICUI_API UUThematicUiSlider : public UThematicUiInteractable
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
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadWrite, Category = "ThematicUi|Slider")
	bool bIsHorizontal = true;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadWrite, Getter, Setter, Category = "ThematicUi|Slider")
	FVector2D ThumbSize = FVector2D(8.0f, 80.0f);
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadWrite, Getter, Setter, Category = "ThematicUi|Text", meta = (MultiLine = "true"))
	FText Text = FText::FromString("Hello");
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadWrite, Category = "ThematicUi|Text")
	bool bAlwaysShowValue = false;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadWrite, Category = "ThematicUi|Text")
	bool bShowValueAsPercentage = false;
	
	UPROPERTY(BlueprintAssignable, Category = "ThematicUi")
	FTUiSliderValueChangedDelegate TUiOnValueChanged;

	private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUi", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UTextBlock> TextBlock;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUi", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UProgressBar> ProgressBar;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUi", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class USlider> Slider;

	
// Class Functions
	public:
	/* Getters and Setters */
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const float GetCurrentValue() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetCurrentValue(const float NewCurrentValue);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	FVector2D GetValueRange() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetValueRange(const FVector2D& NewValueRange);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	float GetStepAmount() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetStepAmount(const float NewStepAmount);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const bool GetbIsHorizontal() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetbIsHorizontal(const bool NewbIsHorizontal);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const FVector2D& GetThumbSize() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetThumbSize(const FVector2D& NewThumbSize);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const FText& GetText() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetText(const FText& NewText);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const bool GetbAlwaysShowValue() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetbAlwaysShowValue(const bool NewbAlwaysShowValue);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const bool GetbShowValueAsPercentage() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetbShowValueAsPercentage(const bool NewbShowValueAsPercentage);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const float GetPercentage() const;
	
	UFUNCTION(BlueprintPure, Category = "ThematicUi|Getters")
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
	virtual void SetThemeNormal() override;
	
	virtual void SetThemeHovered() override;
	
	virtual void SetThemePressed() override;

	protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
	
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

	private:


};
