// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ThematicData/ThematicUIData.h"
#include "ThematicUIThemeData.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = ("ThematicUI"), EditInlineNew)
class THEMATICUI_API UThematicUIThemeDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI")
	UThematicUIThemeDataAsset* ParentThematicUIThemeDataAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI", meta = (EditCondition = "ParentThematicUIThemeDataAsset == nullptr", EditConditionHides))
	FThematicUIThemeData ThematicUIThemeData = (ParentThematicUIThemeDataAsset != nullptr) ? ParentThematicUIThemeDataAsset->GetThematicUIThemeData() : FThematicUIThemeData();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThematicUI", meta = (EditCondition = "ParentThematicUIThemeDataAsset != nullptr", EditConditionHides))
	FThematicUIThemeDataOverride ThematicUIThemeDataOverride = (ParentThematicUIThemeDataAsset != nullptr) ? FThematicUIThemeDataOverride().ConvertFromThemeData(ParentThematicUIThemeDataAsset->ThematicUIThemeData) : FThematicUIThemeDataOverride();
	
public:
	UFUNCTION(BlueprintCallable, Category = "ThematicUI")
	const FThematicUIThemeData& GetThematicUIThemeData();
	
	UFUNCTION(BlueprintCallable, Category = "ThematicUI")
	void SetThematicUIThemeData(const FThematicUIThemeData& NewThematicUIThemeData);
};
