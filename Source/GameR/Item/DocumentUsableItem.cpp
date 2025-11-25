// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/DocumentUsableItem.h"
#include "Item/ItemDocumentData.h"
#include "interface/PlayerHUDInterface.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Controller.h"
#include "Interface/Env/ViewableUI.h"

void UDocumentUsableItem::SetItemData(UItemData* NewData)
{
	Super::SetItemData(NewData);

	UItemDocumentData* data = Cast<UItemDocumentData>(NewData);

	if (data)
	{
		
	}
	
}

void UDocumentUsableItem::Use(APawn* Interactor)
{
	Super::Use(Interactor);

	AController* PlayerController = Interactor->GetController();

	UUserWidget* ui = nullptr;

	if (PlayerController->GetClass()->ImplementsInterface(UPlayerHUDInterface::StaticClass()))
	{
		IPlayerHUDInterface::Execute_RequestShowActorWidget(PlayerController, ViewWidget);
		ui = IPlayerHUDInterface::Execute_GetCurrentWidget(PlayerController);

	}

	if (ui->GetClass()->ImplementsInterface(UViewableUI::StaticClass()))
	{
		IViewableUI::Execute_SetUITexture(ui, this->ItemData->ItemImage);
		IViewableUI::Execute_SetActor(ui, Interactor);
		IViewableUI::Execute_SetItemData(ui, this);
	}
}
