// Fill out your copyright notice in the Description page of Project Settings.


#include "Env/UI/HandLightUI.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Interface/HandLightInterface.h"

void UHandLightUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	GetButton->OnClicked.AddDynamic(this, &UHandLightUI::GetHandLight);
	
}

void UHandLightUI::SetUITexture_Implementation(class UTexture2D* texture)
{
	this->ShowImg = texture;
	DisplayImg->SetBrushFromTexture(ShowImg);	
}

void UHandLightUI::SetItemData_Implementation(class UUsableItem* itemData)
{
	this->ItemData = itemData;	
}

void UHandLightUI::SetActor_Implementation(AActor* actor)
{
	this->Actor = actor;
}

void UHandLightUI::GetHandLight()
{
	APawn* player = GetOwningPlayerPawn();

	if (player->GetClass()->ImplementsInterface(UHandLightInterface::StaticClass()))
	{
		IHandLightInterface::Execute_SetLight(player);
		
		Actor->Destroy();
		CloseWidget();
	}	
}
