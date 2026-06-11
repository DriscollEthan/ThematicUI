// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThematicUIInteractable.h"
#include "ThematicUIDropDownMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTUiOnSelectionChangedSignare, FString, SelectedOption, int, SelectedIndex);

/**
 * 
 */
UCLASS(HideDropdown, NotPlaceable)
class THEMATICUI_API UThematicUIDropDownMenu : public UThematicUIInteractable
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UComboBoxString> ComboBoxString;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UTextBlock> SelectedOptionTextBlock;
	
	UPROPERTY(BlueprintReadOnly, Category = "ThematicUI", meta=(AllowPrivateAccess, BindWidget))
	TObjectPtr<class UImage> DropDownArrowImage;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Setter, Category = "ThematicUI")
	FSlateBrush DropDownArrowBrush;
	
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintReadOnly, Category = "ThematicUI")
	TArray<FString> Options; 
	
	UPROPERTY(BlueprintAssignable, Category = "ThematicUI")
	FTUiOnSelectionChangedSignare OnSelectionChanged;
	
public:
	/* Getters and Setters */
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Getters")
	void SetDropDownArrowBrush(const FSlateBrush& NewDropDownArrowBrush);
	
	UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
	const TArray<FString>& GetOptions() const;
    	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetOptions(const TArray<FString>& NewOptions);
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI|Setters")
	void SetSelectedIndex(const int NewSelectedIndex);
	
	UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
	const FString GetSelectedOption() const;
	
	UFUNCTION(BlueprintPure, Category = "ThematicUI|Getters")
	const int GetSelectedIndex() const;
	
protected:
	UFUNCTION()
	void HandleOpening();
	
	UFUNCTION()
	void HandleSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
	
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	
	virtual void SetThemeNormal() override;
	
	virtual void SetThemeHovered() override;
	
	virtual void SetThemePressed() override;
};
