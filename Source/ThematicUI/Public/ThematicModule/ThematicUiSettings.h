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
UCLASS()
class THEMATICUI_API UThematicUiSettings : public UDeveloperSettings
{
	GENERATED_BODY()


	// Variables 
public:


protected:
	UPROPERTY(EditAnywhere, Category = "Default Input")
	UInputMappingContext* DefaultCommonInputMappingContext;
	
	UPROPERTY(EditAnywhere, Category = "Default Input")
	UInputAction* DefaultClickInputAction;

private:


	// Class Functions
public:
	UInputMappingContext* GetDefaultInputMappingContext() const;
	
	UInputAction* GetDefaultClickInputAction() const;

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
};
