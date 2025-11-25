// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemKey.h"
#include "Interface/Item/UseKey.h"
#include "Item/ItemKeyData.h"
#include "Interface/PlayerHUDInterface.h"
#include "GameFramework/Controller.h"

void UItemKey::SetItemData(UItemData* NewData)
{
	Super::SetItemData(NewData);

	UItemKeyData* keyData = Cast<UItemKeyData>(NewData);

	if (keyData)
		TrueValue = keyData->keycode;

	UE_LOG(LogTemp, Warning, TEXT("key data is inserted"));
}

void UItemKey::Use(APawn* Interactor)
{
	Super::Use(Interactor);

	if (Interactor->GetClass()->ImplementsInterface(UUseKey::StaticClass()))
	{
		IUseKey::Execute_SetKey(Interactor, this->TrueValue);
	}

	
	AController* PlayerController = Interactor->GetController();

	if (PlayerController->GetClass()->ImplementsInterface(UPlayerHUDInterface::StaticClass()))
	{
		
		IPlayerHUDInterface::Execute_RequestHideActorWidget(PlayerController);

	}

	
}
