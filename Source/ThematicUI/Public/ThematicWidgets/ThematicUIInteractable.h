// Fill out your copyright notice in the Description page of Project Settings.

#pragma once




// Includes
	// Compiler Includes
	#include "CoreMinimal.h"

	// Engine Library Includes


	// Project Library Includes
	#include "ThematicUI.h"

	// Class Specific Includes
	#include "Blueprint/UserWidget.h"
	#include "ThematicData/ThematicUIThemeData.h"


	// UE Generated Includes
	#include "ThematicUIInteractable.generated.h"


// Class Details
	// Forward Declarations 
	class USizeBox;
	
	// Delegate Declarations 
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTuiInteractableSetToNormalTheme, UThematicUIInteractable*, Interactable);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTuiInteractableSetToHoveredTheme, UThematicUIInteractable*, Interactable);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTuiInteractableSetToPressedTheme, UThematicUIInteractable*, Interactable);
	
	// Helper Enums 
	
	
	// Helper Structs 



/**
 * 
 */
UCLASS(HideDropdown, NotPlaceable)
class THEMATICUI_API UThematicUIInteractable : public UUserWidget
{
	GENERATED_BODY()

// Variables 
	public:
	UPROPERTY(BlueprintAssignable, Category = "ThematicUI|Events")
	FTuiInteractableSetToNormalTheme OnTuiInteractableSetToNormalTheme;

	UPROPERTY(BlueprintAssignable, Category = "ThematicUI|Events")
	FTuiInteractableSetToHoveredTheme OnTuiInteractableSetToHoveredTheme;

	UPROPERTY(BlueprintAssignable, Category = "ThematicUI|Events")
	FTuiInteractableSetToPressedTheme OnTuiInteractableSetToPressedTheme;
	
	protected:
	/* Widget Theme Data */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI", meta = (DisplayPriority = 1))
	TObjectPtr<UThematicUIThemeDataAsset> WidgetTheme;
	
	/* Widget Theme Data Override */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "ThematicUI", meta = (DisplayPriority = 1))
	FThematicUIThemeDataOverride WidgetThemeOverrideData;
	
	/* Actual Widget Theme Data */
	UPROPERTY(BlueprintReadOnly, Getter, Category = "ThematicUI")
	FThematicUIThemeData ActualThemeData;
	
	/* Size Box Data */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI")
	FVector2D SizeBoxSize = FVector2D(250.0f, 50.0f);
	
	/* Size Box Multiplier When Hovered */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
	FVector2D SizeBoxHoveredSizeMultiplier = FVector2D(1.0f, 1.0f);
	
	/* Size Box Multiplier When Pressed */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
	FVector2D SizeBoxPressedSizeMultiplier = FVector2D(1.0f, 1.0f);

	private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI|Getters", meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<USizeBox> SizeBox;

	
// Class Functions
	public:
	/* Getters and Settes */
		UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
		const FThematicUIThemeDataOverride& GetWidgetThemeOverrideData() const;

		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetWidgetThemeOverrideData(const FThematicUIThemeDataOverride& NewWidgetThemeOverrideData);

		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetWidgetNormalThemeOverrideDate(const FThematicUIThemeOverride& NewWidgetNormalThemeOverride);

		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetWidgetHoveredThemeOverrideDate(const FThematicUIThemeOverride& NewWidgetHoveredThemeOverride);

		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetWidgetPressedThemeOverrideDate(const FThematicUIThemeOverride& NewWidgetPressedThemeOverride);

		UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
		const FThematicUIThemeData& GetActualThemeData() const;

		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void CalculateAndSetActualWidgetThemeData();

		UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
		const FVector2D& GetSizeBoxSize() const;

		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetSizeBoxSize(const FVector2D& NewSizeBoxSize);

	protected:
	

	private:



// Project Class Virtual Functions
	public:


	protected:
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI | SetTheme")
	virtual void SetThemeNormal();
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI | SetTheme")
	virtual void SetThemeHovered();
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI | SetTheme")
	virtual void SetThemePressed();

	private:
	


// Unreal Class Virtual Functions
	public:
	UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
	virtual bool TuiHasUserFocus() PURE_VIRTUAL(UThematicUIInteractable::TuiHasUserFocus, return false;);

	protected:
	/**
	 * NativePreConstruct is to set active theme to NormalTheme and Calculate Actual Theme Data
	 */
	virtual void NativePreConstruct() override;
	
	/**
	 * This will ensure user focus gets set to this widget on MouseHover
	 * @param InGeometry 
	 * @param InMouseEvent 
	 */
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	/**
	 * NativeOnAddedToFocusPath is Called when Widget gains User Focus
	 * @param InFocusEvent 
	 */
	virtual void NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent) override;
	
	/**
	 *  NativeOnFocusLost is Called when Widget gains User Focus
	 * @param InFocusEvent 
	 */
	virtual void NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent) override;

	private:


};
