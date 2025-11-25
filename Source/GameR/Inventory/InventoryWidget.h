// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Common/BaseWidget.h"
#include "InventoryWidget.generated.h"

class UUniformGridPanel;
class UInventoryComponent;
class UInventorySlotWidget;
class UImage;
class UTextBlock;
class UButton;
class UUsableItem;

/**
 * 
 */
UCLASS()
class GAMER_API UInventoryWidget : public UBaseWidget
{
    GENERATED_BODY()

public:
    /** �κ��丮 �����Ϳ� ������ ���� */

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void BindInventory(UInventoryComponent* InventoryToBind);

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UUniformGridPanel* InventoryGrid;

    UPROPERTY(EditAnywhere, Category = "Inventory")
    TSubclassOf<UInventorySlotWidget> SlotWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Layout")
    int32 NumColumns = 5;

    // ���� ���õ� ������
    UPROPERTY(meta = (BindWidget))
    UImage* SelectedItemImage;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* SelectedItemNameText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* SelectedItemDescriptionText;

    UPROPERTY(meta = (BindWidget))
    UButton* UseItemButton;


    UFUNCTION()
    void OnInventoryUpdated();

    UFUNCTION()
    void OnSlotSelected(int32 SelectedIndex);

    UFUNCTION()
    void HandleSlotClicked(int32 ClickedIndex);

    UFUNCTION()
    void HandleUseButtonClicked();

    UFUNCTION()
    void UpdateSelectedItemDetails(class UUsableItem* SelectedItem);


private:
    UPROPERTY()
    UInventoryComponent* BoundInventory;

    UPROPERTY()
    TArray<TObjectPtr<UInventorySlotWidget>> SlotWidgets;
};