#include "InventoryWidget.h"
#include "InventoryComponent.h"
#include "InventorySlotWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Item/UsableItem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void UInventoryWidget::BindInventory(UInventoryComponent* InventoryToBind)
{
    UE_LOG(LogTemp, Warning, TEXT("=== UInventoryWidget::BindInventory Called ==="));

    if (BoundInventory)
    {
        BoundInventory->OnInventoryUpdated.RemoveDynamic(this, &UInventoryWidget::OnInventoryUpdated);
        BoundInventory->OnSlotSelected.RemoveDynamic(this, &UInventoryWidget::OnSlotSelected);
    }

    BoundInventory = InventoryToBind;

    if (!BoundInventory)
    {
        return;
    }

    BoundInventory->OnInventoryUpdated.AddDynamic(this, &UInventoryWidget::OnInventoryUpdated);
    BoundInventory->OnSlotSelected.AddDynamic(this, &UInventoryWidget::OnSlotSelected);

    if (!InventoryGrid || !SlotWidgetClass)
    {
        return;
    }

    InventoryGrid->ClearChildren();
    SlotWidgets.Empty();

    const int32 Capacity = BoundInventory->GetCapacity();
    if (NumColumns <= 0)
    {
        return;
    }

    for (int32 i = 0; i < Capacity; ++i)
    {
        UInventorySlotWidget* NewSlot = CreateWidget<UInventorySlotWidget>(this, SlotWidgetClass);
        if (!NewSlot)
        {
            continue;
        }

        NewSlot->SetSlotIndex(i);
        NewSlot->OnSlotClicked.AddDynamic(this, &UInventoryWidget::HandleSlotClicked);

        int32 Row = i / NumColumns;
        int32 Column = i % NumColumns;

        if (UUniformGridSlot* GridSlot = InventoryGrid->AddChildToUniformGrid(NewSlot, Row, Column))
        {
            GridSlot->SetHorizontalAlignment(HAlign_Fill);
            GridSlot->SetVerticalAlignment(VAlign_Fill);
        }

        SlotWidgets.Add(NewSlot);
    }

    OnInventoryUpdated(); // 초기 UI 갱신
}

void UInventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (UseItemButton)
    {
        UseItemButton->OnClicked.AddDynamic(this, &UInventoryWidget::HandleUseButtonClicked);
        UseItemButton->SetVisibility(ESlateVisibility::Hidden); // 처음엔 숨김
    }
}

void UInventoryWidget::OnInventoryUpdated()
{
    if (!BoundInventory || SlotWidgets.IsEmpty())
    {
        return;
    }

    const int32 MaxSlots = SlotWidgets.Num();

    for (int32 i = 0; i < MaxSlots; ++i)
    {
        if (UInventorySlotWidget* CurrentSlot = SlotWidgets[i].Get())
        {
            UUsableItem* UsableItem = BoundInventory->GetItemByIndex(i);
            CurrentSlot->SetItem(UsableItem);
        }
    }
}

void UInventoryWidget::HandleSlotClicked(int32 ClickedIndex)
{
    if (BoundInventory)
    {
        BoundInventory->SelectSlot(ClickedIndex);
    }
}

void UInventoryWidget::HandleUseButtonClicked()
{
    if (!BoundInventory) {
        return;
    }

    UUsableItem* SelectedItem = BoundInventory->GetSelectedItem();
    if (!SelectedItem) {
        return;
    }

    APlayerController* PlayerController = GetOwningPlayer();
    if (!PlayerController) {
        return;
    }

    APawn* Interactor = PlayerController->GetPawn();
    if (!Interactor) {
        return;
    }

    SelectedItem->Use(Interactor);

    // 아이템 사용 후 인벤토리 업데이트
    BoundInventory->OnInventoryUpdated.Broadcast();
}

void UInventoryWidget::OnSlotSelected(int32 SelectedIndex)
{
    for (int32 i = 0; i < SlotWidgets.Num(); ++i)
    {
        if (SlotWidgets[i])
        {
            SlotWidgets[i]->SetSelectionBorderVisible(i == SelectedIndex);
        }
    }

    if (BoundInventory)
    {
        UUsableItem* SelectedItem = BoundInventory->GetSelectedItem();

        UpdateSelectedItemDetails(SelectedItem);

        if (UseItemButton)
        {
            UseItemButton->SetVisibility(SelectedItem ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
        }
    }
}

void UInventoryWidget::UpdateSelectedItemDetails(UUsableItem* SelectedItem)
{
    // 1. 아이템이 유효한지 확인하고 UI 갱신 시작
    if (SelectedItem)
    {
        // 텍스트 업데이트
        if (SelectedItemNameText)
        {
            SelectedItemNameText->SetText(SelectedItem->GetName());
        }
        if (SelectedItemDescriptionText)
        {
            SelectedItemDescriptionText->SetText(SelectedItem->GetDescription());
        }

        // 이미지 업데이트
        if (SelectedItemImage)
        {
            if (UTexture2D* Texture = SelectedItem->GetItemImage())
            {
                // 아이템 아이콘을 확대 이미지 위젯에 설정
                SelectedItemImage->SetBrushFromTexture(Texture, true);
                SelectedItemImage->SetVisibility(ESlateVisibility::Visible);
            }
            else
            {
                // 이미지가 없으면 숨김
                SelectedItemImage->SetVisibility(ESlateVisibility::Hidden);
            }
        }

        if (UseItemButton)
        {
            UseItemButton->SetVisibility(ESlateVisibility::Visible);
        }
    }
    else
    {
        // 2. 아이템이 선택되지 않았거나 유효하지 않으면 디테일 위젯 숨김/초기화
        if (SelectedItemNameText)
        {
            SelectedItemNameText->SetText(FText::GetEmpty());
        }
        if (SelectedItemDescriptionText)
        {
            SelectedItemDescriptionText->SetText(FText::GetEmpty());
        }
        if (SelectedItemImage)
        {
            // 이미지를 투명하게 만들거나 숨김
            SelectedItemImage->SetVisibility(ESlateVisibility::Hidden);
        }

        if (UseItemButton)
        {
            UseItemButton->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}
