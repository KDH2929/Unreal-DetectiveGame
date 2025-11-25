// Fill out your copyright notice in the Description page of Project Settings.


#include "Env/KeyPad.h"
#include "Interface/Env/KeyDataUI.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/GameModeBase.h"
#include "Interface/Env/LockedActor.h"
#include "GameFramework/PlayerController.h"
#include "Interface/PlayerHUDInterface.h"
#include "Components/StaticMeshComponent.h"
#include "DynamicMesh/DynamicMesh3.h"

// Sets default values
AKeyPad::AKeyPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	KeyPadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	KeyPadMesh->SetupAttachment(RootComponent);
	

}

// Called when the game starts or when spawned
void AKeyPad::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AKeyPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}


void AKeyPad::Interaction_Implementation(APawn* Interactor)
{
	UE_LOG(LogTemp, Log, TEXT("KeyPad Interaction"));

	

	if (KeyPadUI == nullptr || Interactor == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("KeyPadUIClass가 지정되지 않았습니다! (에디터에서 할당 필요), 혹은 Interactor 가 없습니다."));
		return;
	}

	
		
	APawn* Player = Interactor;

	if (Player == nullptr)
	{
		return;
	}

	APlayerController* PlayerController = Player->GetController<APlayerController>();

	if (PlayerController == nullptr)
		return;
	
	IKeyDataUI* KeyPadData = nullptr;
	
	if (PlayerController->GetClass()->ImplementsInterface(UPlayerHUDInterface::StaticClass()))
	{
		IPlayerHUDInterface::Execute_RequestShowActorWidget(PlayerController, KeyPadUI);
		KeyPadData = Cast<IKeyDataUI>(IPlayerHUDInterface::Execute_GetCurrentWidget(PlayerController));
	}
	
	
	if (KeyPadData)
	{
		UE_LOG(LogTemp, Log, TEXT("KeyPad Set Value"));
		KeyPadData->SetKeyData(this->TrueVale);
		KeyPadData->GetCorrectKeyDelegate().AddDynamic(this, &AKeyPad::OpenDoor);
	}
	
}

FString AKeyPad::GetInteractionText_Implementation(APawn* Interactor) const
{
	return Des;
}

void AKeyPad::OpenDoor()
{
	if (LockedActor == nullptr)
		return;
	

	if (LockedActor->GetClass()->ImplementsInterface(ULockedActor::StaticClass()))
	{
		ILockedActor::Execute_UnLock(LockedActor);
	}
	
}
