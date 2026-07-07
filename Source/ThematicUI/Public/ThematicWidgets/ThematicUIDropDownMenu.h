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
	USTRUCT(BlueprintType, Blueprintable)
	struct FThematicUISelectionMenuData
	{
		GENERATED_BODY()
		
		/* Selection Menu Widget Theme Data */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI|SelectionMenuData")
		FThematicUIMainWidgetData SelectionMenuWidgetThemeData;
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI|SelectionMenuData")
		FVector2D SelectionMenuSize = FVector2D(250.0f, 100.0f);
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI|SelectionMenuData")
		FMargin SelectionMenuOptionsPadding = FMargin();
	};
	
	
/**
 * 
 */
UCLASS(HideDropdown, NotPlaceable, Abstract, Category = "ThematicUI")
class THEMATICUI_API UThematicUIDropDownMenu : public UThematicUIInteractable
{
	GENERATED_BODY()

	// Variables 
	public:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI|Events")
	FTUiOnSelectionChangedSignature OnTUiOnSelectionChanged;

	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Category = "ThematicUI")
	TArray<FText> Options;
	
	UPROPERTY()
	int32 SelectedIndex = -1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "ThematicUI")
	FSlateBrush DropDownArrowBrush;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ThematicUI")
	TSubclassOf<UThematicUIDropDownMenuSelection> SelectionMenuSubclass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
	FThematicUISelectionMenuData SelectionMenuData;

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
		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetOptions(const TArray<FText>& NewOptions);
	                                                                                                                              
		UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
		const FSlateBrush& GetDropDownArrowBrush() const;
		
		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetDropDownArrowBrush(const FSlateBrush& NewDropDownArrowBrush);
		
		UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
		const int GetSelectedOption(FText& SelectedOption) const;
		
		UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
		const FThematicUIMainWidgetData& GetSelectionMenuWidgetThemeData() const;
		
		// Doesn't change data until you reopen the selection menu
		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetSelectionMenuWidgetThemeData(const FThematicUIMainWidgetData& NewSelectionMenuWidgetThemeData);
		
		UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
		const FVector2D& GetSelectionMenuSize() const;
		
		// Doesn't change size until you reopen the selection menu
		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetSelectionMenuSize(const FVector2D& NewSelectionMenuSize);
		
		UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
		const FMargin& GetSelectionMenuOptionsPadding() const;
		
		UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
		void SetSelectionMenuOptionsPadding(const FMargin& NewSelectionMenuOptionsPadding);

	protected:
	UFUNCTION()
	void HandleDropDownButtonPressed(UThematicUIButton* PressedButton);
	
	UFUNCTION()
	void HandleOptionSelected(int SelectedOptionIndex);

	private:
	


// Project Class Virtual Functions
	public:
	virtual void SetThemeNormal() override;
	
	virtual void SetThemeHovered() override;
	
	virtual void SetThemePressed() override;

	protected:
	
	
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
