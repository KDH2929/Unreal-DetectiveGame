// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/Env/KeyDataUI.h"
#include "Blueprint/UserWidget.h"
#include "Common/BaseWidget.h"
#include "KeyPadUI.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class GAMER_API UKeyPadUI : public UBaseWidget, public IKeyDataUI 
{
	GENERATED_BODY()

// UI Design	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> InputDisplay;
	
protected:
	FKeyValueCorrect CorrectkKeyValue;	
	
	virtual FKeyValueCorrect& GetCorrectKeyDelegate() override;

	FString keyValue;
	FString TrueValue;
	
	virtual void SetKeyData(FString data) override;

	UFUNCTION(BlueprintCallable, Category="KeyPad")
	void MatchKeyData();

	UFUNCTION(BlueprintCallable, Category="KeyPad")
	void AppendKey(FString Key);

	UFUNCTION(BlueprintCallable, Category="KeyPad")
	void ClearKeyData();

	UFUNCTION(BlueprintCallable, Category="KeyPad")
	void Backspace();

	
protected:
	virtual void NativeConstruct() override;
};
