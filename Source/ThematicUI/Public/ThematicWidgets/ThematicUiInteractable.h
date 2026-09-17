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
	#include "ThematicData/ThematicUiThemeData.h"


	// UE Generated Includes
	#include "ThematicUiInteractable.generated.h"


// Class Details
	// Forward Declarations 
	class USizeBox;
	
	// Delegate Declarations 
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTuiInteractableSetToNormalTheme, UThematicUiInteractable*, Interactable);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTuiInteractableSetToHoveredTheme, UThematicUiInteractable*, Interactable);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTuiInteractableSetToPressedTheme, UThematicUiInteractable*, Interactable);
	
	// Helper Enums 

	
	// Helper Structs 
	USTRUCT(BlueprintType, Blueprintable)
	struct FThematicUIMainWidgetData
	{
		GENERATED_BODY()
		
		public:
		/* Widget Theme Data */
			UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUi")
			TObjectPtr<UThematicUiThemeDataAsset> WidgetTheme;
			
			/* Widget Theme Data Override */
			UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUi")
			FThematicUIThemeDataOverride WidgetThemeOverrideData;
			
			/* Size Box Data */
			UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUi")
			FVector2D SizeBoxSize = FVector2D(250.0f, 50.0f);
			
			/* Size Box Multiplier When Hovered */
			UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUi")
			FVector2D SizeBoxHoveredSizeMultiplier = FVector2D(1.0f, 1.0f);
			
			/* Size Box Multiplier When Pressed */
			UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUi")
			FVector2D SizeBoxPressedSizeMultiplier = FVector2D(1.0f, 1.0f);
	};


/**
 * 
 */
UCLASS(HideDropdown, NotPlaceable, Abstract, Category = "ThematicUi")
class THEMATICUI_API UThematicUiInteractable : public UUserWidget
{
	GENERATED_BODY()

// Variables 
	public:
	UPROPERTY(BlueprintAssignable, Category = "ThematicUi|Events")
	FTuiInteractableSetToNormalTheme OnTuiInteractableSetToNormalTheme;

	UPROPERTY(BlueprintAssignable, Category = "ThematicUi|Events")
	FTuiInteractableSetToHoveredTheme OnTuiInteractableSetToHoveredTheme;

	UPROPERTY(BlueprintAssignable, Category = "ThematicUi|Events")
	FTuiInteractableSetToPressedTheme OnTuiInteractableSetToPressedTheme;
	
	protected:
	/* Primary Widget Data */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "ThematicUi", meta = (DisplayPriority = 1))
	FThematicUIMainWidgetData PrimaryWidgetData;
	
	/* Actual Widget Theme Data */
	UPROPERTY(BlueprintReadOnly, Getter, Category = "ThematicUi")
	FThematicUiThemeData ActualThemeData;
	
	UPROPERTY(EditAnywhere, Category = "ThematicUi|Subclass")
	TSubclassOf<UThematicUiInteractable> BlueprintVerisionSubclass;

	private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUi", meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<USizeBox> SizeBox;

	
// Class Functions
	public:
	/* Getters and Settes */
		UFUNCTION(BlueprintPure, Category = "ThematicUi|Getters")
		const FThematicUIMainWidgetData& GetPrimaryWidgetData() const;
		
		UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
		void SetPrimaryWidgetData(const FThematicUIMainWidgetData& NewPrimaryWidgetData);

		UFUNCTION(BlueprintPure, Category = "ThematicUi|Getters")
		const FThematicUiThemeData& GetActualThemeData() const;
		
		UFUNCTION(BlueprintPure, Category = "ThematicUi|Getters")
		UThematicUiThemeDataAsset* GetWidgetTheme() const;
		
		UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
		void SetWidgetTheme(UThematicUiThemeDataAsset* NewWidgetTheme);
		
		UFUNCTION(BlueprintPure, Category = "ThematicUi|Getters")
		const FThematicUIThemeDataOverride& GetWidgetThemeOverrideData() const;
		
		UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
		void SetWidgetThemeOverrideData(FThematicUIThemeDataOverride NewWidgetThemeOverrideData);

		// Returns Normal SizeBoxSize
		UFUNCTION(BlueprintPure, Category = "ThematicUi|Getters")
		const FVector2D& GetSizeBoxSize() const;

		UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
		void SetSizeBoxSize(const FVector2D& NewSizeBoxSize);
		
		UFUNCTION(BlueprintPure, Category = "ThematicUi|Getters")
		const FVector2D& GetSizeBoxHoveredSizeMultiplier() const;
		
		UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
		void SetSizeBoxHoveredSizeMultiplier(const FVector2D& NewSizeBoxHoveredSizeMultiplier);
		
		UFUNCTION(BlueprintPure, Category = "ThematicUi|Getters")
		const FVector2D& GetSizeBoxPressedSizeMultiplier() const;
		
		UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
		void SetSizeBoxPressedSizeMultiplier(const FVector2D& NewSizeBoxPressedSizeMultiplier);
		
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void CalculateAndSetActualWidgetThemeData();

	protected:
	

	private:


// Virtual Functions
	public:
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUi|SetTheme")
	virtual void SetThemeNormal();
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUi|SetTheme")
	virtual void SetThemeHovered();
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUi|SetTheme")
	virtual void SetThemePressed();
	
	UFUNCTION(BlueprintPure, Category = "ThematicUi|Getters")
	virtual bool TuiHasUserFocus() PURE_VIRTUAL(UThematicUIInteractable::TuiHasUserFocus, return false;);

	
	
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;

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
