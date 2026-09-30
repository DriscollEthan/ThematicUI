// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



// Includes
	// Compiler Includes
	#include "CoreMinimal.h"

	// Engine Library Includes
	#include "Framework/Text/TextLayout.h"

	// Project Library Includes
	

	// Class Specific Includes
	#include "ThematicUiInteractable.h"

// UE Generated Includes
	#include "ThematicUITextBlock.generated.h"


// Class Details
	// Forward Declarations 
	
	
	// Delegate Declarations 
	
	
	// Helper Enums 
	
	
	// Helper Structs 

/**
 * 
 */
UCLASS(HideDropdown, NotPlaceable, Abstract, Category = "ThematicUi", PrioritizeCategories("ThematicUi"))
class THEMATICUI_API UThematicUiTextBlock : public UThematicUiInteractable
{
	GENERATED_BODY()

	// Variables 
	public:


	protected:
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Setter, Category = "ThematicUi", meta = (MultiLine = "true"))
	FText Text;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUi")
	float LineHeightPercentage = 1.0f;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUi")
	TEnumAsByte<ETextJustify::Type> Justification = ETextJustify::Left;

	private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUi", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UBorder> Border;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUi", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UTextBlock> TextBlock;

	
// Class Functions
	public:
	/* Getters and Setters */
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const FText& GetText() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetText(const FText& NewText);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const float GetLineHeightPercentage() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetLineHeightPercentage(float NewLineHeightPercentage);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Getters")
	const ETextJustify::Type GetJustification() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi|Setters")
	void SetJustification(const ETextJustify::Type& NewJustification);

	protected:
	

	private:


// Virtual Functions
	public:
	virtual void SetThemeNormal() override;
	
	virtual void SetThemeHovered() override;
	
	virtual void SetThemePressed() override;

	protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;

	private:
	

};
