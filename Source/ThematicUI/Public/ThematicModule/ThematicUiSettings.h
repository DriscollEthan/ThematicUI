// Fill out your copyright notice in the Description page of Project Settings.


#pragma once


// Includes
// Compiler Includes
#include "CoreMinimal.h"

// Engine Library Includes


// Project Library Includes
#include <Engine/DeveloperSettings.h>

// Class Specific Includes


// UE Generated Includes
#include "ThematicUiSettings.generated.h"


// Class Details
	// Forward Declarations 
	class UInputMappingContext;
	class UInputAction;
	
	// Delegate Declarations 
	
	
	// Helper Enums 
	
	
	// Helper Structs 
	

/**
 * 
 */
UCLASS(config = Game, defaultconfig)
class THEMATICUI_API UThematicUiSettings : public UDeveloperSettings
{
	GENERATED_BODY()


	// Variables 
public:


protected:
	UPROPERTY(Config, EditAnywhere, Category = "Default Input", Meta=(AllowAbstract=false))
	TSoftObjectPtr<UInputMappingContext> DefaultInputMappingContext;
	
	UPROPERTY(Transient)
	TObjectPtr<UInputMappingContext> DefaultCommonInputMappingContextClass;
	
	UPROPERTY(Config, EditAnywhere, Category = "Default Input", Meta=(AllowAbstract=false))
	TSoftObjectPtr<UInputAction> DefaultClickInputAction;
	
	UPROPERTY(Transient)
	TObjectPtr<UInputAction> DefaultClickInputActionClass;

private:
	bool bInputDataLoaded = false;

	// Class Functions
public:
	UInputMappingContext* GetDefaultInputMappingContext() const;
	
	UInputAction* GetDefaultClickInputAction() const;
	
	void LoadData();

protected:


private:
	void LoadInputData();

	// Project Class Virtual Functions
public:


protected:


private:
	// Unreal Class Virtual Functions
public:


protected:


private:
};
