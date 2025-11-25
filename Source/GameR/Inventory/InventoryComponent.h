#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItemData;
class UUsableItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotSelected, int32, SelectedIndex);


UCLASS()
class GAMER_API UInventoryComponent : public UActorComponent    
{
    GENERATED_BODY()

public:
    UInventoryComponent();

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool AddItem(UItemData* NewItemData);

    bool AddItem(UUsableItem* ExistingItem);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void RemoveItemByIndex(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    UUsableItem* GetItemByIndex(int32 SlotIndex) const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    int32 GetNumItems() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    int32 GetCapacity() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool IsFull() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool IsEmpty() const;

    // 선택 슬롯 관리 로직 추가
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void SelectSlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    UUsableItem* GetSelectedItem() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    int32 GetSelectedSlotIndex() const { return SelectedSlotIndex; }

    UFUNCTION(BlueprintCallable, Category = "Inventory|Debug")
    void DebugPrintInventory();

    UPROPERTY(BlueprintAssignable)
    FOnInventoryUpdated OnInventoryUpdated;

    UPROPERTY(BlueprintAssignable)
    FOnSlotSelected OnSlotSelected;

    

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items")
    TArray<TObjectPtr<UUsableItem>> UsableItems;

    UPROPERTY(EditAnywhere, Category = "Inventory")
    int32 MaxCapacity = 20;

private:
    UPROPERTY(SaveGame)
    int32 CurrentNumItems = 0;

    

    UPROPERTY()
    int32 SelectedSlotIndex = INDEX_NONE;
};