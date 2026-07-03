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
	#include "ThematicUIDropDownMenu.generated.h"


// Class Details
	// Forward Declarations 
	class UThematicUIButton;
	class UImage;
	class UThematicUIDropDownMenuSelection;
	
	// Delegate Declarations 
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTUiOnSelectionChangedSignare, FString, SelectedOption, int, SelectedIndex);
	
	// Helper Enums 
	
	
	// Helper Structs 

/**
 * 
 */
UCLASS(HideDropdown, NotPlaceable)
class THEMATICUI_API UThematicUIDropDownMenu : public UThematicUIInteractable
{
	GENERATED_BODY()

	// Variables 
	public:
	

	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	TArray<FText> Options;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	TSubclassOf<UThematicUIDropDownMenuSelection> SelectionMenuSubclass;
	
	/* Selection Menu Widget Theme Data */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI|SelectionMenuData")
	TObjectPtr<UThematicUIThemeDataAsset> SelectionMenuWidgetTheme;
	
	/* Selection Menu Widget Theme Data Override */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "ThematicUI|SelectionMenuData")
	FThematicUIThemeDataOverride SelectionMenuWidgetThemeOverrideData;
	
	/* Selection Menu Actual Widget Theme Data */
	UPROPERTY(BlueprintReadOnly, Getter, Category = "ThematicUI|SelectionMenuData")
	FThematicUIThemeData SelectionMenuActualThemeData;
	
	/* Selection Menu Size Box Data */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI|SelectionMenuData")
	FVector2D SelectionMenuSizeBoxSize = FVector2D(250.0f, 50.0f);
	
	/* Selection Menu Size Box Multiplier When Hovered */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI|SelectionMenuData")
	FVector2D SelectionMenuSizeBoxHoveredSizeMultiplier = FVector2D(1.0f, 1.0f);
	
	/* Selection Menu Size Box Multiplier When Pressed */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI|SelectionMenuData")
	FVector2D SelectionMenuSizeBoxPressedSizeMultiplier = FVector2D(1.0f, 1.0f);

	private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<UThematicUIButton> DropDownButton;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<UImage> DropDownArrowImage;


	
// Class Functions
	public:
	/* Getters and Settes */
		UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
		const FThematicUIThemeDataOverride& GetSelectionMenuWidgetThemeOverrideData() const;

		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetSelectionMenuWidgetThemeOverrideData(const FThematicUIThemeDataOverride& NewWidgetThemeOverrideData);

		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetSelectionMenuWidgetNormalThemeOverrideDate(const FThematicUIThemeOverride& NewWidgetNormalThemeOverride);

		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetSelectionMenuWidgetHoveredThemeOverrideDate(const FThematicUIThemeOverride& NewWidgetHoveredThemeOverride);

		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetSelectionMenuWidgetPressedThemeOverrideDate(const FThematicUIThemeOverride& NewWidgetPressedThemeOverride);

		UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
		const FThematicUIThemeData& GetSelectionMenuActualThemeData() const;

		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SelectionMenuCalculateAndSetActualWidgetThemeData();

		UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
		const FVector2D& GetSelectionMenuSizeBoxSize() const;

		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetSelectionMenuSizeBoxSize(const FVector2D& NewSizeBoxSize);
	

	protected:
	

	private:



// Project Class Virtual Functions
	public:


	protected:
	virtual void SetThemeNormal() override;
	
	virtual void SetThemeHovered() override;
	
	virtual void SetThemePressed() override;

	private:
	


// Unreal Class Virtual Functions
	public:


	protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
	
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

	private:

	
};
