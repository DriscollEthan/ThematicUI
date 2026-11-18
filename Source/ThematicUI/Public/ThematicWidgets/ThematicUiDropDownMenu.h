// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



// Includes
	// Compiler Includes
	#include "CoreMinimal.h"

	// Engine Library Includes


	// Project Library Includes
	

	// Class Specific Includes
	#include "ThematicUiInteractable.h"

// UE Generated Includes
	#include "ThematicUiDropDownMenu.generated.h"


// Class Details
	// Forward Declarations 
	class UThematicUiButton;
	class UImage;
	class UThematicUiDropDownMenuSelection;
	
	// Delegate Declarations 
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTUiOnSelectionChangedSignature, FText, SelectedOption, int, SelectedIndex);
	
	// Helper Enums 
	UENUM(Blueprintable, BlueprintType)
	enum class ESelectionMenuBackground : uint8 
	{
		None,
		Image,
		BackgroundBlur
	};
	
	// Helper Structs 
	USTRUCT(BlueprintType, Blueprintable)
	struct FThematicUISelectionMenuData
	{
		GENERATED_BODY()
		
		/* Selection Menu Widget Theme Data */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUi|SelectionMenuData")
		FThematicUIMainWidgetData SelectionMenuWidgetThemeData;
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUi|SelectionMenuData")
		FVector2D SelectionMenuSize = FVector2D(250.0f, 100.0f);
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUi|SelectionMenuData")
		FVector2D SelectionMenuRelativePosition = FVector2D(0.0f, 0.0f);
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUi|SelectionMenuData")
		FMargin SelectionMenuOptionsPadding = FMargin();
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUi|SelectionMenuData")
		ESelectionMenuBackground SelectionMenuBackground = ESelectionMenuBackground::None;
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUi|SelectionMenuData", meta = (EditCondition = "SelectionMenuBackground == ESelectionMenuBackground::Image", EditConditionHides))
		FSlateBrush BackgroundImageBrush = FSlateBrush();
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUi|SelectionMenuData", meta = (EditCondition = "SelectionMenuBackground == ESelectionMenuBackground::BackgroundBlur", EditConditionHides))
		float BackgroundBlurStrength = 50.0f;
	};
	
	
/**
 * 
 */
UCLASS(HideDropdown, NotPlaceable, Abstract, Category = "ThematicUi", PrioritizeCategories("ThematicUi"))
class THEMATICUI_API UThematicUiDropDownMenu : public UThematicUiInteractable
{
	GENERATED_BODY()

	// Variables 
	public:
	UPROPERTY(BlueprintAssignable, Category = "ThematicUi|Events")
	FTUiOnSelectionChangedSignature OnTUiOnSelectionChanged;

	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Category = "ThematicUi")
	TArray<FText> Options;
	
	UPROPERTY()
	int32 SelectedIndex = -1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "ThematicUi")
	FSlateBrush DropDownArrowBrush;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ThematicUi")
	TSubclassOf<UThematicUiDropDownMenuSelection> SelectionMenuSubclass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUi")
	FThematicUISelectionMenuData SelectionMenuData;

	private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUi", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<UThematicUiButton> DropDownButton;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUi", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<UImage> DropDownArrowImage;
	
	UPROPERTY()
	TObjectPtr<UThematicUiDropDownMenuSelection> SelectionMenu;

	
// Class Functions
	public:
	/* Getters and Setters */                                              
		UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
		void SetOptions(const TArray<FText>& NewOptions);
	                                                                                                                              
		UFUNCTION(BlueprintPure, Category = "ThematicUi|Getters")
		const FSlateBrush& GetDropDownArrowBrush() const;
		
		UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
		void SetDropDownArrowBrush(const FSlateBrush& NewDropDownArrowBrush);
		
		UFUNCTION(BlueprintPure, Category = "ThematicUi|Getters")
		const int GetSelectedOption(FText& SelectedOption) const;
		
		UFUNCTION(BlueprintPure, Category = "ThematicUi|Getters")
		const FThematicUIMainWidgetData& GetSelectionMenuWidgetThemeData() const;
		
		// Doesn't change data until you reopen the selection menu
		UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
		void SetSelectionMenuWidgetThemeData(const FThematicUIMainWidgetData& NewSelectionMenuWidgetThemeData);
		
		UFUNCTION(BlueprintPure, Category = "ThematicUi|Getters")
		const FVector2D& GetSelectionMenuSize() const;
		
		// Doesn't change size until you reopen the selection menu
		UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
		void SetSelectionMenuSize(const FVector2D& NewSelectionMenuSize);
		
		UFUNCTION(BlueprintPure, Category = "ThematicUi|Getters")
		const FMargin& GetSelectionMenuOptionsPadding() const;
		
		UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
		void SetSelectionMenuOptionsPadding(const FMargin& NewSelectionMenuOptionsPadding);

	protected:
	UFUNCTION()
	void HandleDropDownButtonPressed(UThematicUiButton* PressedButton);
	
	UFUNCTION()
	void HandleOptionSelected(int SelectedOptionIndex);

	private:
	

// Virtual Functions
	public:
	virtual void SetThemeNormal() override;
	
	virtual void SetThemeHovered() override;
	
	virtual void SetThemePressed() override;

	protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
	
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	
	virtual void NativeDestruct() override;

	private:

	
};
