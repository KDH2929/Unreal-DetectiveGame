// Fill out your copyright notice in the Description page of Project Settings.


#include "Env/UI/ViewableActorUI.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Interface/InventoryInterface.h"
#include "Item/UsableItem.h"
#include "Item/DocumentUsableItem.h"
#include "Inventory/InventoryComponent.h"
#include "Item/ItemDocumentData.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

void UViewableActorUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	GetButton->OnClicked.AddDynamic(this, &UViewableActorUI::AddToInventory);
}

void UViewableActorUI::SetUITexture_Implementation(class UTexture2D* texture)
{
	this->ShowImg = texture;
	DisplayImg->SetBrushFromTexture(ShowImg, true);
	
}

void UViewableActorUI::SetItemData_Implementation(class UUsableItem* itemData)
{
	this->ItemData = itemData;
	
	UItemDocumentData* data = Cast<UItemDocumentData>(itemData->GetItemData());

	if (data != nullptr)
	{
		DesTextBlock->SetText(data->DocumentContent[0]);
	}
	
	
}

void UViewableActorUI::SetActor_Implementation(AActor* actor)
{
	this->Actor = actor;
}

void UViewableActorUI::AddToInventory()
{
	APawn* OwningPawn = GetOwningPlayerPawn();
	
	if (OwningPawn == nullptr)
	{
		return;
	}

	UInventoryComponent* inventory = nullptr;
	if (OwningPawn->GetClass()->ImplementsInterface(UInventoryInterface::StaticClass()))
	{
		inventory = IInventoryInterface::Execute_GetInventoryComponent(OwningPawn);
		inventory->AddItem(ItemData);
		Actor->Destroy();
		CloseWidget();
	}
}
