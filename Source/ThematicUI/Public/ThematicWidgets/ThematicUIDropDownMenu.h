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
	class UComboBoxString;
	class UTextBlock;
	class UImage;
	
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Setter, Category = "ThematicUI")
	FSlateBrush DropDownArrowBrush;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI")
	TArray<FString> Options; 
	
	UPROPERTY(BlueprintAssignable, Category = "ThematicUI")
	FTUiOnSelectionChangedSignare OnSelectionChanged;

	protected:
	

	private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<UComboBoxString> ComboBoxString;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<UTextBlock> SelectedOptionTextBlock;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<UImage> DropDownArrowImage;

	
// Class Functions
	public:
	/* Getters and Setters */ 
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	void SetDropDownArrowBrush(const FSlateBrush& NewDropDownArrowBrush);
	
	UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
	const TArray<FString>& GetOptions() const;
    	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetOptions(const TArray<FString>& NewOptions);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetSelectedIndex(const int NewSelectedIndex);
	
	UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
	const FString GetSelectedOption() const;
	
	UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
	const int GetSelectedIndex() const;

	protected:
	UFUNCTION()
	void HandleOpening();
	
	UFUNCTION()
	void HandleSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

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
