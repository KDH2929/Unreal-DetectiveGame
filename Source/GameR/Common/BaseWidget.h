// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseWidget.generated.h"

class UBackgroundBlur;
/**
 * 
 */
UCLASS()
class GAMER_API UBaseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category="KeyPad")
	void CloseWidget();

	UFUNCTION()
	void OnCloseButtonClicked();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> BackGroundImg;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UBackgroundBlur> BackgroundBlur;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> CloseButton;

	virtual void NativeConstruct() override;
	
	
};
