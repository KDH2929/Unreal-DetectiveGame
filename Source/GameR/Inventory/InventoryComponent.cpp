#include "InventoryComponent.h"
#include "Item/ItemData.h"
#include "Item/UsableItem.h"
#include "Engine/Engine.h"

UInventoryComponent::UInventoryComponent()
{
    UsableItems.SetNum(MaxCapacity);
    CurrentNumItems = 0;
}

bool UInventoryComponent::AddItem(UItemData* NewItemData)
{
    DebugPrintInventory();

    if (!NewItemData)
    {
        return false;
    }

    if (IsFull())
    {
        UsableItems.Add(nullptr);
        MaxCapacity++;
    }

    // 빈 슬롯 탐색
    for (int32 i = 0; i < UsableItems.Num(); ++i)
    {
        if (UsableItems[i] == nullptr)
        {
            // UsableItem 객체 생성
            UUsableItem* NewUsableItem = NewObject<UUsableItem>(this, UUsableItem::StaticClass());
            NewUsableItem->SetItemData(NewItemData);

            UsableItems[i] = NewUsableItem;
            ++CurrentNumItems;

            OnInventoryUpdated.Broadcast();
            return true;
        }
    }

    return false; // 빈 슬롯 없음
}

bool UInventoryComponent::AddItem(UUsableItem* ExistingItem)
{
    if (!ExistingItem)
    {
        return false;
    }

    if (IsFull())
    {
        UsableItems.Add(nullptr);
        MaxCapacity++;
    }

    for (int32 i = 0; i < UsableItems.Num(); ++i)
    {
        if (UsableItems[i] == nullptr)
        {
            UsableItems[i] = ExistingItem;
            ++CurrentNumItems;
            OnInventoryUpdated.Broadcast();
            return true;
        }
    }
    return false;
}

void UInventoryComponent::RemoveItemByIndex(int32 SlotIndex)
{
    if (UsableItems.IsValidIndex(SlotIndex) && UsableItems[SlotIndex] != nullptr)
    {
        UsableItems[SlotIndex] = nullptr;
        --CurrentNumItems;

        OnInventoryUpdated.Broadcast();
    }
}

UUsableItem* UInventoryComponent::GetItemByIndex(int32 SlotIndex) const
{
    if (UsableItems.IsValidIndex(SlotIndex))
    {
        return UsableItems[SlotIndex];
    }
    return nullptr;
}

int32 UInventoryComponent::GetNumItems() const
{
    return CurrentNumItems;
}

int32 UInventoryComponent::GetCapacity() const
{
    return MaxCapacity;
}

bool UInventoryComponent::IsFull() const
{
    return GetNumItems() >= GetCapacity();
}

bool UInventoryComponent::IsEmpty() const
{
    return GetNumItems() == 0;
}

void UInventoryComponent::SelectSlot(int32 SlotIndex)
{
    if (UsableItems.IsValidIndex(SlotIndex))
    {
        SelectedSlotIndex = SlotIndex;
        UE_LOG(LogTemp, Log, TEXT("Selected Slot: %d"), SlotIndex);
        OnSlotSelected.Broadcast(SlotIndex);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid slot index: %d"), SlotIndex);
    }
}

UUsableItem* UInventoryComponent::GetSelectedItem() const
{
    if (UsableItems.IsValidIndex(SelectedSlotIndex))
    {
        return UsableItems[SelectedSlotIndex];
    }
    return nullptr;
}

void UInventoryComponent::DebugPrintInventory()
{
    UE_LOG(LogTemp, Warning, TEXT("--- Current Inventory Status (Capacity: %d/%d) ---"), GetNumItems(), MaxCapacity);

    
    
    for (int32 i = 0; i < UsableItems.Num(); i++)
    {
        const UUsableItem* Item = UsableItems[i];

        if (IsValid(Item) && Item->GetItemData())
        {
            FString ItemName = Item->GetItemData()->Name.ToString();

            UE_LOG(LogTemp, Warning, TEXT("Slot [%d]: %s"), i, *ItemName);
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Slot [%d]: %s"), i, *ItemName));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Slot [%d]: EMPTY or Invalid UsableItem"), i);
        }
    }
}
