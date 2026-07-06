// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



// Includes
	// Compiler Includes
	#include "CoreMinimal.h"

	// Engine Library Includes
	#include "Framework/Text/TextLayout.h"

	// Project Library Includes
	

	// Class Specific Includes
	#include "ThematicUIInteractable.h"

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
UCLASS(HideDropdown, NotPlaceable)
class THEMATICUI_API UThematicUITextBlock : public UThematicUIInteractable
{
	GENERATED_BODY()

	// Variables 
	public:


	protected:
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Setter, Category = "ThematicUI", meta = (MultiLine = "true"))
	FText Text;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI")
	float LineHeightPercentage = 1.0f;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI")
	TEnumAsByte<ETextJustify::Type> Justification = ETextJustify::Left;

	private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UBorder> Border;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UTextBlock> TextBlock;

	
// Class Functions
	public:
	/* Getters and Setters */
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const FText& GetText() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetText(const FText& NewText);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const float GetLineHeightPercentage() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetLineHeightPercentage(float NewLineHeightPercentage);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const ETextJustify::Type GetJustification() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetJustification(const ETextJustify::Type& NewJustification);

	protected:
	

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

	private:
	

};
