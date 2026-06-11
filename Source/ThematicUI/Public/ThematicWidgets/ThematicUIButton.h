// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThematicWidgets/ThematicUIInteractable.h"
#include "ThematicUIButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTUiButtonPressedDelegate);

/**
 * 
 */
UCLASS(HideDropdown, NotPlaceable)
class THEMATICUI_API UThematicUIButton : public UThematicUIInteractable
{
	GENERATED_BODY()
	
private:
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UButton> Button;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UTextBlock> TextBlock;
	
protected:
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI", meta = (MultiLine = "true"))
	FText Text;
	
	UPROPERTY(BlueprintAssignable, Category = "ThematicUI")
	FTUiButtonPressedDelegate TUiButtonPressed;

public:
	/* Getters and Setters */
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	const FText& GetText() const;
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetText(const FText& NewText);
	
protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
	
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	
	virtual void SetThemeNormal() override;
	
	virtual void SetThemeHovered() override;
	
	virtual void SetThemePressed() override;
	
	UFUNCTION()
	void HandleButtonPressed();
	
	UFUNCTION()
	void HandleButtonReleased();
};
