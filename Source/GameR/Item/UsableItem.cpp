// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/UsableItem.h"
#include "Engine/Engine.h"
#include "Interface/PlayerHUDInterface.h"
#include "GameFramework/Controller.h"
#include "Engine/Texture2D.h"

UUsableItem::UUsableItem()
{
	ItemData = nullptr;
	Name = FText::FromString(TEXT("Unnamed"));
	ItemImage = nullptr;
	Description = FText();
}

void UUsableItem::PostInitProperties()
{
	Super::PostInitProperties();

	if (ItemData)
	{
		Name = ItemData->Name;

		
		;
		ItemImage = ItemData->ItemImage;
		Description = ItemData->Description;
	}
}

void UUsableItem::SetItemData(UItemData* NewData)
{
	ItemData = NewData;

	if (ItemData)
	{
		Name = ItemData->Name;
		ItemImage = ItemData->ItemImage;
		Description = ItemData->Description;
	}
}

UItemData* UUsableItem::GetItemData() const
{
	return ItemData;
}

void UUsableItem::SetName(const FText& NewName)
{
	Name = NewName;
}

FText UUsableItem::GetName() const
{
	return Name;
}

void UUsableItem::SetItemImage(UTexture2D* NewImage)
{
	ItemImage = NewImage;
}

UTexture2D* UUsableItem::GetItemImage() const
{
	return ItemImage;
}

void UUsableItem::SetDescription(const FText& NewDescription)
{
	Description = NewDescription;
}

FText UUsableItem::GetDescription() const
{
	return Description;
}

void UUsableItem::Use(APawn* Interactor)
{
	AController* PlayerController = Interactor->GetController();

	if (PlayerController->GetClass()->ImplementsInterface(UPlayerHUDInterface::StaticClass()))
	{
		
		IPlayerHUDInterface::Execute_RequestHideActorWidget(PlayerController);

	}

	
}
