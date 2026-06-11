// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThematicUIInteractable.h"
#include "Framework/Text/TextLayout.h"
#include "ThematicUITextBlock.generated.h"

/**
 * 
 */
UCLASS(HideDropdown, NotPlaceable)
class THEMATICUI_API UThematicUITextBlock : public UThematicUIInteractable
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UBorder> Border;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UTextBlock> TextBlock;
	
protected:
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Setter, Category = "ThematicUI", meta = (MultiLine = "true"))
	FText Text;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI")
	float LineHeightPercentage = 1.0f;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI")
	TEnumAsByte<ETextJustify::Type> Justification = ETextJustify::Left;
	
	
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
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
	
	virtual void SetThemeNormal() override;
	
	virtual void SetThemeHovered() override;
	
	virtual void SetThemePressed() override;
};
