// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ViewableUI.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UViewableUI : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMER_API IViewableUI
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UI")
	void SetUITexture(class UTexture2D* texture);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UI")
	void SetItemData(class UUsableItem* itemData);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UI")
	void SetActor(AActor* actor);

	
};
