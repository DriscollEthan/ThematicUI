// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


// Includes
	// Compiler Includes
	#include "CoreMinimal.h"

	// Engine Library Includes


	// Project Library Includes
	#include "ThematicData/ThematicUIData.h"

	// Class Specific Includes
	#include "Engine/DataAsset.h"

	// UE Generated Includes
	#include "ThematicUIThemeData.generated.h"


// Class Details
	// Forward Declarations 
	
	
	// Delegate Declarations 
	
	
	// Helper Enums 
	
	
	// Helper Structs 


/**
 * 
 */
UCLASS(ClassGroup = ("ThematicUI"))
class THEMATICUI_API UThematicUIThemeDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
	
	// Variables 
	public:


	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	TObjectPtr<UThematicUIThemeDataAsset> ParentThematicUIThemeDataAsset = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI", meta = (EditCondition = "ParentThematicUIThemeDataAsset == nullptr", EditConditionHides))
	FThematicUIThemeData ThematicUIThemeData = (ParentThematicUIThemeDataAsset != nullptr) ? ParentThematicUIThemeDataAsset->GetThematicUIThemeData() : FThematicUIThemeData();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI", meta = (EditCondition = "ParentThematicUIThemeDataAsset != nullptr", EditConditionHides))
	FThematicUIThemeDataOverride ThematicUIThemeDataOverride = (ParentThematicUIThemeDataAsset != nullptr) ? FThematicUIThemeDataOverride().ConvertFromThemeData(ParentThematicUIThemeDataAsset->ThematicUIThemeData) : FThematicUIThemeDataOverride();

	private:
	

	
// Class Functions
	public:
	UFUNCTION(BlueprintPure, Category = "ThematicUI")
	const FThematicUIThemeData& GetThematicUIThemeData();
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI")
	void SetThematicUIThemeData(const FThematicUIThemeData& NewThematicUIThemeData);
	
	UFUNCTION(BlueprintPure, Category = "ThematicUI")
	const FThematicUIThemeDataOverride GetThematicUIThemeDataOverride();

	protected:
	

	private:



// Project Class Virtual Functions
	public:
	

	protected:
	

	private:
	


// Unreal Class Virtual Functions
	public:
	

	protected:
	

	private:
	#if WITH_EDITOR
		virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif

};

