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
	
	
	// Helper Enums 
	
	
	// Helper Structs 


/**
 * 
 */
UCLASS()
class THEMATICUI_API UThematicUIDropDownMenuSelection : public UThematicUIInteractable
{
	GENERATED_BODY()


	// Variables 
	public:


	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	TArray<FText> Options;

	private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta = (AllowPrivateAccess, BindWidget))
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
	
	
	protected:
	
	
	private:
	

	// Project Class Virtual Functions
	public:
	
	
	protected:
	
	
	private:
	

	// Unreal Class Virtual Functions
	public:
	
	
	protected:
	
	
	private:
	
	
};
