#include "InventorySlotWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Item/UsableItem.h"
#include "Engine/Texture2D.h"

void UInventorySlotWidget::NativeConstruct()
{
    Super::NativeConstruct();

    UE_LOG(LogTemp, Warning, TEXT("SLOT WIDGET CONSTRUCTED. Index: %d"), SlotIndex);

    if (SlotButton)
    {
        SlotButton->OnClicked.AddDynamic(this, &UInventorySlotWidget::HandleButtonClicked);

        UE_LOG(LogTemp, Warning, TEXT("Slot [%d]: SlotButton BOUND OK."), SlotIndex);
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("Slot [%d]: SlotButton is NULL! Check UMG 'Is Variable'."), SlotIndex);
    }

    if (SelectionBorder)
    {
        SelectionBorder->SetVisibility(ESlateVisibility::Hidden);

        UE_LOG(LogTemp, Warning, TEXT("Slot [%d]: SelectionBorder BOUND OK."), SlotIndex);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Slot [%d]: SelectionBorder is NULL! Check UMG 'Is Variable'."), SlotIndex);
    }
}

void UInventorySlotWidget::SetItem(UUsableItem* UsableItem)
{
    BoundUsableItem = UsableItem;

    if (UsableItem && ItemImage)
    {
        if (UTexture2D* Texture = UsableItem->GetItemImage())
        {
            ItemImage->SetBrushFromTexture(Texture, true);
            ItemImage->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            ItemImage->SetVisibility(ESlateVisibility::Hidden);
        }
    }
    else if (ItemImage)
    {
        ItemImage->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UInventorySlotWidget::SetSelectionBorderVisible(bool bVisible)
{
    if (SelectionBorder)
    {
        SelectionBorder->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }
}

void UInventorySlotWidget::HandleButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("Slot [%d]: BUTTON CLICKED! Broadcasting."), SlotIndex);

    OnSlotClicked.Broadcast(SlotIndex);
}
