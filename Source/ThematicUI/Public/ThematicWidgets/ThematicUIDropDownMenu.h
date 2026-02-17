// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThematicUIInteractable.h"
#include "ThematicUIDropDownMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTUiOnSelectionChangedSignare, FString, SelectedOption, int, SelectedIndex);

/**
 * 
 */
UCLASS()
class THEMATICUI_API UThematicUIDropDownMenu : public UThematicUIInteractable
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class USizeBox> SizeBox;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UComboBoxString> ComboBoxString;
	
	UPROPERTY(EditDefaultsOnly, Category = "ThematicUI")
	FSlateBrush DropDownArrowBrush;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
	FVector2D SizeBoxSize = FVector2D(250.0f, 50.0f);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThematicUI")
	TArray<FString> Options; 
	
	UPROPERTY(BlueprintAssignable, Category = "ThematicUI")
	FTUiOnSelectionChangedSignare OnSelectionChanged;
	
public:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
	
	virtual void SetThemeNormal() override;
	
	virtual void SetThemeHovered() override;
	
	virtual void SetThemePressed() override;
	
public:
	UFUNCTION()
	void HandleOpening();
	
	UFUNCTION()
	void HandleSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
};
