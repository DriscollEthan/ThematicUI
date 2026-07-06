// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


// Includes
	// Compiler Includes
	#include "CoreMinimal.h"

	// Engine Library Includes


	// Project Library Includes
	

	// Class Specific Includes
	#include "ThematicWidgets/ThematicUIInteractable.h"

	// UE Generated Includes
	#include "ThematicUIButton.generated.h"



// Class Details
	// Forward Declarations 
	class UButton;
	class UTextBlock;
	
	// Delegate Declarations 
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTuiButtonPressedAndReleased, UThematicUIButton*, Button);
	
	// Helper Enums 
	
	
	// Helper Structs 



/**
 * 
 */
UCLASS(HideDropdown, NotPlaceable)
class THEMATICUI_API UThematicUIButton : public UThematicUIInteractable
{
	GENERATED_BODY()

	// Variables 
	public:
	UPROPERTY(BlueprintAssignable, Category = "ThematicUI|Events")
	FTuiButtonPressedAndReleased OnTuiButtonPressedAndReleased;

	protected:
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI", meta = (MultiLine = "true"))
	FText Text;

	private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<UButton> Button;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<UTextBlock> TextBlock;

	
// Class Functions
	public:
	/* Getters and Setters */
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const FText& GetText() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetText(const FText& NewText);
	
	protected:
	UFUNCTION()
	void HandleButtonPressed();
	
	UFUNCTION()
	void HandleButtonReleased();

	private:



// Project Class Virtual Functions
	public:
	virtual bool TuiHasUserFocus() override;
	
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

	private:


};
