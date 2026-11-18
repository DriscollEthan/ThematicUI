// Fill out your copyright notice in the Description page of Project Settings.

#pragma once




// Includes
	// Compiler Includes
	#include "CoreMinimal.h"

	// Engine Library Includes
	

	// Project Library Includes
	#include "ThematicUI.h"

	// Class Specific Includes
	#include <Blueprint/WidgetTree.h>
	#include "CommonInputModeTypes.h"
	#include "CommonUserWidget.h"	
	#include "ThematicData/ThematicUiThemeData.h"


	// UE Generated Includes
	#include "ThematicUiInteractable.generated.h"


// Class Details
	// Forward Declarations 
	class USizeBox;
	struct FDataTableRowHandle;
	class UInputAction;
	struct FUIActionBindingHandle;
	
	// Delegate Declarations 
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTuiInteractableThemeChangedSignature, UThematicUiInteractable*, Interactable);
	
	// Helper Enums 
	UENUM()
	enum class ETuiCurrentTheme : uint8
	{  
		Default,
		Hovered,
		Pressed
	};
	
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
UCLASS(HideDropdown, Abstract, ClassGroup = "ThematicUi", HideCategories("Appearance","Interaction","Performance","Localization","Designer","Input"), Category = "ThematicUi", PrioritizeCategories("ThematicUi"))
class THEMATICUI_API UThematicUiInteractable : public UCommonUserWidget
{
	GENERATED_BODY()

// Variables 
	public:
	UPROPERTY(BlueprintAssignable, Category = "ThematicUi|Events")
	FTuiInteractableThemeChangedSignature OnTuiInteractableSetToNormalTheme;

	UPROPERTY(BlueprintAssignable, Category = "ThematicUi|Events")
	FTuiInteractableThemeChangedSignature OnTuiInteractableSetToHoveredTheme;

	UPROPERTY(BlueprintAssignable, Category = "ThematicUi|Events")
	FTuiInteractableThemeChangedSignature OnTuiInteractableSetToPressedTheme;
	
	protected:
	/* Primary Widget Data */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "ThematicUi", meta = (DisplayPriority = 1))
	FThematicUIMainWidgetData PrimaryWidgetData;
	
	/* Actual Widget Theme Data */
	UPROPERTY(BlueprintReadOnly, Getter, Category = "ThematicUi")
	FThematicUiThemeData ActualThemeData;
	
	UPROPERTY(EditAnywhere, Category = "ThematicUi|Subclass", meta = (DeprecatedProperty, DeprecationMessage="TUI DEPCRECATED PROPERTY"))
	TSubclassOf<UThematicUiInteractable> BlueprintVerisionSubclass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUi|Input Data")
	TEnumAsByte<EButtonPressMethod::Type> PressMethod = EButtonPressMethod::ButtonPress;
	
	/** The type of mouse action required by the user to trigger the button's 'Click' */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUi|Input Data")
	TEnumAsByte<EButtonClickMethod::Type> ClickMethod = EButtonClickMethod::DownAndUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUi|Input Data")
	TEnumAsByte<EButtonTouchMethod::Type> TouchMethod = EButtonTouchMethod::DownAndUp;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUi|Input Data")
	bool bButtonEnabled = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUi|Input Data")
	bool bInteractionEnabled = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUi|Input Data")
	bool bIsPersistentBinding = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUi|Input Data")
	ECommonInputMode OverrideInputMode = ECommonInputMode::Menu;
	
	/** 
	 *	The enhanced input action that is bound to this button. The common input manager will trigger this button to 
	 *	click if the action was pressed 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUi|Input Data", meta = (EditCondition = "CommonInput.CommonInputSettings.IsEnhancedInputSupportEnabled", EditConditionHides))
	TObjectPtr<UInputAction> TriggeringEnhancedInputAction;
	
	FUIActionBindingHandle TriggeringBindingHandle;
	
	FUIActionBindingHandle DefaultTriggeringBindingHandle;

	private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUi", meta = (AllowPrivateAccess, BindWidget, DeprecatedProperty))
	TObjectPtr<USizeBox> OldSizeBox;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUi", meta = (AllowPrivateAccess))
	TObjectPtr<USizeBox> SizeBox;
	
	UPROPERTY()
	ETuiCurrentTheme CurrentTheme = ETuiCurrentTheme::Default;

	
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
	void AddWidgetToSizeBox(UWidget* WidgetToAdd);
	
	private:


// Virtual Functions
	public:
	virtual bool Initialize() override;
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUi")
	virtual void SetThemeNormal();
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUi")
	virtual void SetThemeHovered();
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "ThematicUi")
	virtual void SetThemePressed();
	
	UFUNCTION(BlueprintPure, Category = "ThematicUi|Getters")
	virtual bool TuiHasUserFocus() const { return CurrentTheme == ETuiCurrentTheme::Hovered || CurrentTheme == ETuiCurrentTheme::Pressed; }

	protected:
	/**
	 * NativePreConstruct is to set active theme to NormalTheme and Calculate Actual Theme Data
	 */
	virtual void NativePreConstruct() override;

	/**
	 * NativeConstruct will call input binding into Common UI
	 */
	virtual void NativeConstruct() override;
	
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
	// @todo Make PURE_VIRTUAL
	virtual void BindTriggeringInputActionToClick() {}

};
