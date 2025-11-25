// Fill out your copyright notice in the Description page of Project Settings.


#include "Env/ExitDoor.h"
#include "TimerManager.h"
#include "interface/PlayerHUDInterface.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Controller.h"

void AExitDoor::Interaction_Implementation(APawn* Interactor)
{
	Super::Interaction_Implementation(Interactor);

	

	if (!bIsLock)
	{
		Player = Interactor;

		ui = nullptr;

		AController* PlayerController = Interactor->GetController();
	
		if (PlayerController->GetClass()->ImplementsInterface(UPlayerHUDInterface::StaticClass()))
		{
			IPlayerHUDInterface::Execute_RequestShowActorWidget(PlayerController, TeleportWidget);
			ui = IPlayerHUDInterface::Execute_GetCurrentWidget(PlayerController);

		}
		
		GetWorld()->GetTimerManager().SetTimer(
		MyTimerHandle, 
		this, 
		&AExitDoor::Teleport, 
		3.0f, 
		false
		);
	}

}

void AExitDoor::Teleport_Timer()
{
}

void AExitDoor::Teleport()
{
	Player->TeleportTo(TeleportPos, TeleportRot);


	APlayerController* PlayerController = ui->GetOwningPlayer();
	
	if (PlayerController->GetClass()->ImplementsInterface(UPlayerHUDInterface::StaticClass()))
	{
		IPlayerHUDInterface::Execute_RequestHideActorWidget(PlayerController);
	}
	
}
