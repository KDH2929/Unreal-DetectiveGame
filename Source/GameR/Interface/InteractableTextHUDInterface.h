// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableTextHUDInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractableTextHUDInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMER_API IInteractableTextHUDInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUD")
	void ShowInteractionText(const FString& Message);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUD")
	void HideInteractionText();
	
};
