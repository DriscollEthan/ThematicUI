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
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTUiOnSelectionChangedSignature, FText, SelectedOption, int, SelectedIndex);
	
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
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI|Events")
	FTUiOnSelectionChangedSignature OnTUiOnSelectionChanged;

	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	TArray<FText> Options;
	
	UPROPERTY()
	int32 SelectedIndex = -1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "ThematicUI")
	FSlateBrush DropDownArrowBrush;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	TSubclassOf<UThematicUIDropDownMenuSelection> SelectionMenuSubclass;
	
	/* Selection Menu Widget Theme Data */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Category = "ThematicUI|SelectionMenuData")
	FThematicUIMainWidgetData SelectionMenuWidgetThemeData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Category = "ThematicUI|SelectionMenuData")
	FVector2D SelectionMenuSize = FVector2D(250.0f, 100.0f);

	private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<UThematicUIButton> DropDownButton;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<UImage> DropDownArrowImage;
	
	UPROPERTY()
	TObjectPtr<UThematicUIDropDownMenuSelection> SelectionMenu;

	
// Class Functions
	public:
	/* Getters and Setters */                                                                                                                                                                            
		UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
		const FSlateBrush& GetDropDownArrowBrush() const;
		
		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetDropDownArrowBrush(const FSlateBrush& NewDropDownArrowBrush);
		
		UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
		const int GetSelectedOption(FText& SelectedOption) const;
		
		// Doesn't change data until you reopen the selection menu
		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetSelectionMenuWidgetThemeData(const FThematicUIMainWidgetData& NewSelectionMenuWidgetThemeData);
		
		// Doesn't change size until you reopen the selection menu
		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetSelectionMenuSize(const FVector2D& NewSelectionMenuSize);

	protected:
	UFUNCTION()
	void HandleDropDownButtonPressed(UThematicUIButton* PressedButton);
	
	UFUNCTION()
	void HandleOptionSelected(int SelectedOptionIndex);

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
	
	virtual void NativeDestruct() override;

	private:

	
};
