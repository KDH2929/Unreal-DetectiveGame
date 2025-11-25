// Fill out your copyright notice in the Description page of Project Settings.


#include "Env/ViewableActor.h"
#include "interface/PlayerHUDInterface.h"
#include "GameFramework/Controller.h"
#include "Blueprint/UserWidget.h"
#include "Interface/Env/ViewableUI.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "Item/ItemKey.h"
#include "Item/UsableItem.h"
#include "Item/ItemData.h"

// Sets default values
AViewableActor::AViewableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	KeyPadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	KeyPadMesh->SetupAttachment(RootComponent);

	EngineSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("EngineSoundComponent"));
	EngineSoundComponent->SetupAttachment(RootComponent);
	EngineSoundComponent->SetAutoActivate(false);

}

// Called when the game starts or when spawned
void AViewableActor::BeginPlay()
{
	Super::BeginPlay();

	UsableItemInstance = NewObject<UUsableItem>(GetOuter(), UsableItem);
	
	
	

	if (ItemDatav)
	{
		UsableItemInstance->SetItemData(ItemDatav);
		InteractionText = ItemDatav->InteractionText.ToString();
	}
		
	
	
}

// Called every frame
void AViewableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AViewableActor::Interaction_Implementation(APawn* Interactor)
{
	AController* PlayerController = Interactor->GetController();
	
	if (PlayerController == nullptr or ViewWidget == nullptr or UsableItemInstance == nullptr or ItemDatav == nullptr)
		return;

	UUserWidget* ui = nullptr;
	
	if (PlayerController->GetClass()->ImplementsInterface(UPlayerHUDInterface::StaticClass()))
	{
		EngineSoundComponent->SetSound(OnInteractionSound);
		EngineSoundComponent->Play();
		
		IPlayerHUDInterface::Execute_RequestShowActorWidget(PlayerController, ViewWidget);
		ui = IPlayerHUDInterface::Execute_GetCurrentWidget(PlayerController);

	}

	if (ui->GetClass()->ImplementsInterface(UViewableUI::StaticClass()))
	{
		IViewableUI::Execute_SetUITexture(ui, UsableItemInstance->GetItemImage());
		IViewableUI::Execute_SetActor(ui, this);
		IViewableUI::Execute_SetItemData(ui, this->UsableItemInstance);
	}
	
}

FString AViewableActor::GetInteractionText_Implementation(APawn* Interactor) const
{
	return InteractionText;
}

