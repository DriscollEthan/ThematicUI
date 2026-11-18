// Fill out your copyright notice in the Description page of Project Settings.


#include "ThematicModule/ThematicUiSettings.h"

UInputMappingContext* UThematicUiSettings::GetDefaultInputMappingContext() const
{
	return DefaultCommonInputMappingContext;
}

UInputAction* UThematicUiSettings::GetDefaultClickInputAction() const
{
	return DefaultClickInputAction;
}
