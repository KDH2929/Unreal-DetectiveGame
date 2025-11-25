// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.generated.h"

class UButton;
class UImage;
class UUsableItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotClicked, int32, SlotIndex);

/**
 * 
 */
UCLASS()
class GAMER_API UInventorySlotWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetItem(UUsableItem* UsableItem);

    void SetSlotIndex(int32 Index) { SlotIndex = Index; }

    void SetSelectionBorderVisible(bool bVisible);

    UPROPERTY(BlueprintAssignable, Category = "Inventory|Event")
    FOnSlotClicked OnSlotClicked;

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UButton* SlotButton;

    UPROPERTY(meta = (BindWidget))
    UImage* ItemImage;

    UPROPERTY(meta = (BindWidgetOptional))
    UImage* SelectionBorder;

private:
    UPROPERTY()
    TObjectPtr<UUsableItem> BoundUsableItem;

    int32 SlotIndex = INDEX_NONE;

    UFUNCTION()
    void HandleButtonClicked();
};