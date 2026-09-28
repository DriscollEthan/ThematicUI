// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


// Includes
	// Compiler Includes
	#include "CoreMinimal.h"

	// Engine Library Includes


	// Project Library Includes
	

	// Class Specific Includes
	#include "ThematicWidgets/ThematicUiInteractable.h"

// UE Generated Includes
	#include "ThematicUiButton.generated.h"



// Class Details
	// Forward Declarations 1
	class UButton;
	class UTextBlock;
	
	// Delegate Declarations 
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTuiButtonPressedAndReleased, UThematicUiButton*, Button);
	
	// Helper Enums 
	
	
	// Helper Structs 



/**
 * 
 */
UCLASS(HideDropdown, NotPlaceable, Abstract, Category = "ThematicUi", PrioritizeCategories("ThematicUi"))
class THEMATICUI_API UThematicUiButton : public UThematicUiInteractable
{
	GENERATED_BODY()

	// Variables 
	public:
	UPROPERTY(BlueprintAssignable, Category = "ThematicUi|Events")
	FTuiButtonPressedAndReleased OnTuiButtonPressedAndReleased;

	protected:
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUi", meta = (MultiLine = "true"))
	FText Text;

	private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUi", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<UButton> Button;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUi", meta=(AllowPrivateAccess, BindWidget))
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
	virtual bool TuiHasUserFocus() override;
	
	virtual void SetThemeNormal() override;
	
	virtual void SetThemeHovered() override;
	
	virtual void SetThemePressed() override;

	protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
	
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

	private:


};
