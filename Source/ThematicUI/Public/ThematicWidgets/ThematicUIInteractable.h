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
	USTRUCT(BlueprintType, Blueprintable)
	struct FThematicUIMainWidgetData
	{
		GENERATED_BODY()
		
		public:
		/* Widget Theme Data */
			UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
			TObjectPtr<UThematicUIThemeDataAsset> WidgetTheme;
			
			/* Widget Theme Data Override */
			UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
			FThematicUIThemeDataOverride WidgetThemeOverrideData;
			
			/* Size Box Data */
			UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
			FVector2D SizeBoxSize = FVector2D(250.0f, 50.0f);
			
			/* Size Box Multiplier When Hovered */
			UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
			FVector2D SizeBoxHoveredSizeMultiplier = FVector2D(1.0f, 1.0f);
			
			/* Size Box Multiplier When Pressed */
			UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
			FVector2D SizeBoxPressedSizeMultiplier = FVector2D(1.0f, 1.0f);
	};


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
	/* Primary Widget Data */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "ThematicUI", meta = (DisplayPriority = 1))
	FThematicUIMainWidgetData PrimaryWidgetData;
	
	/* Actual Widget Theme Data */
	UPROPERTY(BlueprintReadOnly, Getter, Category = "ThematicUI")
	FThematicUIThemeData ActualThemeData;

	private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<USizeBox> SizeBox;

	
// Class Functions
	public:
	/* Getters and Settes */
		UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
		const FThematicUIMainWidgetData& GetPrimaryWidgetData() const;
		
		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetPrimaryWidgetData(const FThematicUIMainWidgetData& NewPrimaryWidgetData);

		UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
		const FThematicUIThemeData& GetActualThemeData() const;
		
		UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
		UThematicUIThemeDataAsset* GetWidgetTheme() const;
		
		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetWidgetTheme(UThematicUIThemeDataAsset* NewWidgetTheme);
		
		UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
		const FThematicUIThemeDataOverride& GetWidgetThemeOverrideData() const;
		
		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetWidgetThemeOverrideData(FThematicUIThemeDataOverride NewWidgetThemeOverrideData);

		// Returns Normal SizeBoxSize
		UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
		const FVector2D& GetSizeBoxSize() const;

		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetSizeBoxSize(const FVector2D& NewSizeBoxSize);
		
		UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
		const FVector2D& GetSizeBoxHoveredSizeMultiplier() const;
		
		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetSizeBoxHoveredSizeMultiplier(const FVector2D& NewSizeBoxHoveredSizeMultiplier);
		
		UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
		const FVector2D& GetSizeBoxPressedSizeMultiplier() const;
		
		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetSizeBoxPressedSizeMultiplier(const FVector2D& NewSizeBoxPressedSizeMultiplier);
		
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void CalculateAndSetActualWidgetThemeData();

	protected:
	

	private:



// Project Class Virtual Functions
	public:
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI | SetTheme")
	virtual void SetThemeNormal();
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI | SetTheme")
	virtual void SetThemeHovered();
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUI | SetTheme")
	virtual void SetThemePressed();

	protected:
	

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
