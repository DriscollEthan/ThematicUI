// Fill out your copyright notice in the Description page of Project Settings.


#pragma once


// Includes
	// Compiler Includes
	#include "CoreMinimal.h"
	
	// Engine Library Includes
	
	
	// Project Library Includes
	#include "ThematicUIInteractable.h"
	
	// Class Specific Includes
	#include "ThematicWidgets/ThematicUIDropDownMenu.h"
	
	// UE Generated Includes
	#include "ThematicUIDropDownMenuSelection.generated.h"


// Class Details
	// Forward Declarations 
	class UScrollBox;
	class UThematicUIButton;
	
	// Delegate Declarations 
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTuiOnOptionSelectedSignature, int, SelectedIndex);
	
	// Helper Enums 
	
	
	// Helper Structs 


/**
 * Marked as Experimental to hide from Widget Design Palette
 */
UCLASS(HideDropdown, NotPlaceable, Abstract, Category = "ThematicUI", Experimental)
class THEMATICUI_API UThematicUIDropDownMenuSelection : public UThematicUIInteractable
{
	GENERATED_BODY()


	// Variables 
	public:
	UPROPERTY(BlueprintAssignable, Category = "ThematicUI|Events")
	FTuiOnOptionSelectedSignature OnTuiOnOptionSelected;

	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	TArray<FText> Options;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ThematicUI")
	TSubclassOf<UThematicUIButton> DropDownButtonSubclass;
	
	UPROPERTY(BlueprintReadWrite, Category = "ThematicUI")
	FThematicUISelectionMenuData SelectionMenuData;

	private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta = (AllowPrivateAccess))
	TObjectPtr<UThematicUIDropDownMenu> OwningDropDownMenuRef;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<UScrollBox> ScrollBox;
	
	/**
	 * This map tracks the buttons used for selecting the option in the DropDownMenu
	 * @param Button Pointer = Button in options menu
	 * @param int = index of where the option tied to this button is stored in the options array.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta = (AllowPrivateAccess))
	TMap<TObjectPtr<UThematicUIButton>, int> SelectionButtonsMap;


	// Class Functions
	public:
	UFUNCTION(BlueprintPure, Category = "ThematicUI|Getter")
	bool CheckUserFocus();
	
	protected:
	void HandleTickCheckForUserFocus();
	
	void CreateOptionButtons();
	
	void SetupButtonNavigation();
	
	UFUNCTION()
	void HandleOptionSelected(UThematicUIButton* ButtonPressed);
	
	private:
	void HandleOptionSelected(int32 SelectedIndex);
	
	void UpdatePosition();

	// Project Class Virtual Functions
	public:
	virtual void NativeCreated(UThematicUIDropDownMenu* OwnerMenu, TArray<FText>& OptionsArray, const FThematicUISelectionMenuData& NewData);
	
	protected:
	
	
	private:
	

	// Unreal Class Virtual Functions
	public:
	
	
	protected:	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	virtual void NativeDestruct() override;
	
	private:
	
	
};
