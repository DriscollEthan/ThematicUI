// Fill out your copyright notice in the Description page of Project Settings.


#pragma once


// Includes
	// Compiler Includes
	#include "CoreMinimal.h"
	
	// Engine Library Includes
	
	
	// Project Library Includes
	#include "ThematicUiInteractable.h"
	
// Class Specific Includes
	#include "ThematicWidgets/ThematicUiDropDownMenu.h"
	
// UE Generated Includes
	#include "ThematicUiDropDownMenuSelection.generated.h"


// Class Details
	// Forward Declarations 
	class UBackgroundBlur;
	class UImage;
	class UScrollBox;
	class UThematicUiButton;
	
	// Delegate Declarations 
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTuiOnOptionSelectedSignature, int, SelectedIndex);
	
	// Helper Enums 
	
	
	// Helper Structs 


/**
 * Marked as Experimental to hide from Widget Design Palette
 */
UCLASS(HideDropdown, NotPlaceable, Abstract, Category = "ThematicUi", Experimental, PrioritizeCategories("ThematicUi"))
class THEMATICUI_API UThematicUiDropDownMenuSelection : public UThematicUiInteractable
{
	GENERATED_BODY()


	// Variables 
	public:
	UPROPERTY(BlueprintAssignable, Category = "ThematicUi|Events")
	FTuiOnOptionSelectedSignature OnTuiOnOptionSelected;

	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUi")
	TArray<FText> Options;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ThematicUi")
	TSubclassOf<UThematicUiButton> DropDownButtonSubclass;
	
	UPROPERTY(BlueprintReadWrite, Category = "ThematicUi")
	FThematicUISelectionMenuData SelectionMenuData;

	private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUi", meta = (AllowPrivateAccess))
	TObjectPtr<UThematicUiDropDownMenu> OwningDropDownMenuRef;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUi", meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<UBackgroundBlur> BackgroundBlur;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUi", meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<UImage> BackgroundImage;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUi", meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<UScrollBox> ScrollBox;
	
	/**
	 * This map tracks the buttons used for selecting the option in the DropDownMenu
	 * @param Button Pointer = Button in options menu
	 * @param int = index of where the option tied to this button is stored in the options array.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUi", meta = (AllowPrivateAccess))
	TMap<TObjectPtr<UThematicUiButton>, int> SelectionButtonsMap;


	// Class Functions
	public:
	UFUNCTION(BlueprintPure, Category = "ThematicUi|Getter")
	bool CheckUserFocus();
	
	protected:
	void HandleTickCheckForUserFocus();
	
	void CreateOptionButtons();
	
	void SetupButtonNavigation();
	
	UFUNCTION()
	void HandleOptionSelected(UThematicUiButton* ButtonPressed);
	
	private:
	void HandleOptionSelected(int32 SelectedIndex);
	
	void UpdatePosition();


// Virtual Functions
	public:
		virtual void NativeCreated(UThematicUiDropDownMenu* OwnerMenu, TArray<FText>& OptionsArray, const FThematicUISelectionMenuData& NewData);

	
	protected:	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	virtual void NativeDestruct() override;
	
	private:
	
	
};
