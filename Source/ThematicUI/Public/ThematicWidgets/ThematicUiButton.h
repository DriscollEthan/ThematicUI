// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


// Includes
	// Compiler Includes
	#include "CoreMinimal.h"

	// Engine Library Includes


	// Project Library Includes
	

	// Class Specific Includes
	#include "CommonButtonBase.h"
	#include "ThematicWidgets/ThematicUiInteractable.h"

	// UE Generated Includes
	#include "ThematicUiButton.generated.h"



// Class Details
	// Forward Declarations
	class UButton;
	class UTextBlock;
	
	// Delegate Declarations
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTuiButtonInteractionSignature, UThematicUiButton*, Button);
	
	// Helper Enums 
	
	
	// Helper Structs 



/**
 * 
 */
UCLASS(HideDropdown, Category = "ThematicUi", PrioritizeCategories("ThematicUi"))
class THEMATICUI_API UThematicUiButton : public UThematicUiInteractable
{
	GENERATED_BODY()

	// Variables 
	public:
	UPROPERTY(BlueprintAssignable, Category = "ThematicUi|Events")
	FTuiButtonInteractionSignature OnTuiButtonPressedDelegate;
	
	UPROPERTY(BlueprintAssignable, Category = "ThematicUi|Events")
	FTuiButtonInteractionSignature OnTuiButtonReleasedDelegate;
	
	UPROPERTY(BlueprintAssignable, Category = "ThematicUi|Events")
	FTuiButtonInteractionSignature OnTuiButtonClickedDelegate;

	protected:
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUi", meta = (MultiLine = "true"))
	FText Text;

	private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUi", meta=(AllowPrivateAccess))
	TObjectPtr<UCommonButtonInternalBase> CommonButton;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUi", meta=(AllowPrivateAccess))
	TObjectPtr<UTextBlock> TextBlock;

	
// Class Functions
	public:
	/* Getters and Setters */
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const FText& GetText() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetText(const FText& NewText);
	
	protected:
	UFUNCTION()
	void HandleButtonPressed();
	
	UFUNCTION()
	void HandleButtonReleased();

	private:

// Virtual Functions
	public:
	virtual bool Initialize() override;
	
	virtual void SetThemeNormal() override;
	
	virtual void SetThemeHovered() override;
	
	virtual void SetThemePressed() override;

	protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
	
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

	private:
	virtual void BindTriggeringInputActionToClick() override;

};
