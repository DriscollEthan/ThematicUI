// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



// Includes
	// Compiler Includes
	#include "CoreMinimal.h"

	// Engine Library Includes
#include "Widgets/Notifications/SProgressBar.h"

	// Project Library Includes
	

	// Class Specific Includes
	#include "ThematicUIInteractable.h"

	// UE Generated Includes
	#include "UThematicUISlider.generated.h"


// Class Details
	// Forward Declarations 
	
	
	// Delegate Declarations 
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTUiSliderValueChangedDelegate, float, NewValue);
	
	// Helper Enums 
	
	
	// Helper Structs 

/**
 * 
 */
UCLASS(HideDropdown, NotPlaceable)
class THEMATICUI_API UUThematicUISlider : public UThematicUIInteractable
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
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadWrite, Category = "ThematicUI|Slider")
	bool bIsHorizontal = true;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadWrite, Getter, Setter, Category = "ThematicUI|Slider")
	FVector2D ThumbSize = FVector2D(8.0f, 80.0f);
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadWrite, Getter, Setter, Category = "ThematicUI|Text", meta = (MultiLine = "true"))
	FText Text = FText::FromString("Hello");
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadWrite, Category = "ThematicUI|Text")
	bool bAlwaysShowValue = false;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadWrite, Category = "ThematicUI|Text")
	bool bShowValueAsPercentage = false;
	
	UPROPERTY(BlueprintAssignable, Category = "ThematicUI")
	FTUiSliderValueChangedDelegate TUiOnValueChanged;

	private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UTextBlock> TextBlock;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UProgressBar> ProgressBar;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class USlider> Slider;

	
// Class Functions
	public:
	/* Getters and Setters */
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
	const bool GetbShowValueAsPercentage() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetbShowValueAsPercentage(const bool NewbShowValueAsPercentage);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const float GetPercentage() const;
	
	UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
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
