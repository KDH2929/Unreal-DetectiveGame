// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Common/BaseWidget.h"
#include "InteractionWidget.generated.h"

UCLASS()
class GAMER_API UInteractionWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidgetOptional))
    class UTextBlock* InteractionText;

public:
    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void SetInteractionText(const FText& NewText);
};