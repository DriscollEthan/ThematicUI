// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


// Includes
	// Compiler Includes
	#include "CoreMinimal.h"

	// Engine Library Includes


	// Project Library Includes
	#include "ThematicData/ThematicUiData.h"

// Class Specific Includes
	#include "Engine/DataAsset.h"

	// UE Generated Includes
	#include "ThematicUiThemeData.generated.h"


// Class Details
	// Forward Declarations 
	
	
	// Delegate Declarations 
	
	
	// Helper Enums 
	
	
	// Helper Structs 


/**
 * 
 */
UCLASS(ClassGroup = ("ThematicUi"))
class THEMATICUI_API UThematicUiThemeDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
	
	// Variables 
	public:


	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUi")
	TObjectPtr<UThematicUiThemeDataAsset> ParentThematicUIThemeDataAsset = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUi", meta = (EditCondition = "ParentThematicUIThemeDataAsset == nullptr", EditConditionHides))
	FThematicUiThemeData ThematicUIThemeData = (ParentThematicUIThemeDataAsset != nullptr) ? ParentThematicUIThemeDataAsset->GetThematicUIThemeData() : FThematicUiThemeData();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUi", meta = (EditCondition = "ParentThematicUIThemeDataAsset != nullptr", EditConditionHides))
	FThematicUIThemeDataOverride ThematicUIThemeDataOverride = (ParentThematicUIThemeDataAsset != nullptr) ? FThematicUIThemeDataOverride().ConvertFromThemeData(ParentThematicUIThemeDataAsset->ThematicUIThemeData) : FThematicUIThemeDataOverride();

	private:
	

	
// Class Functions
	public:
	UFUNCTION(BlueprintPure, Category = "ThematicUi")
	const FThematicUiThemeData& GetThematicUIThemeData();
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUi")
	void SetThematicUIThemeData(const FThematicUiThemeData& NewThematicUIThemeData);
	
	UFUNCTION(BlueprintPure, Category = "ThematicUi")
	const FThematicUIThemeDataOverride GetThematicUIThemeDataOverride();

	protected:
	

	private:


// Virtual Functions
	public:
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;

	protected:
	

	private:
	#if WITH_EDITOR
		virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif

};

