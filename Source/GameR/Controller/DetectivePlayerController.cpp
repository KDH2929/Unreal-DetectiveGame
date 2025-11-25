// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/DetectivePlayerController.h"
#include "Game/GameRCameraManager.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameR.h"
#include "InputMappingContext.h"
#include "Widgets/Input/SVirtualJoystick.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Env/UI/InteractionWidget.h"
#include "GameFramework/Character.h"


ADetectivePlayerController::ADetectivePlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AGameRCameraManager::StaticClass();
}

void ADetectivePlayerController::ShowInteractionText_Implementation(const FString& Message)
{
	if (InteractionWidgetInstance)
	{
		InteractionWidgetInstance->SetInteractionText(FText::FromString(Message));
		InteractionWidgetInstance->AddToViewport();
		InteractionWidgetInstance->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ShowInteractionText called, but InteractionWidgetInstance is null."));
	}
}

void ADetectivePlayerController::HideInteractionText_Implementation()
{
	if (InteractionWidgetInstance && InteractionWidgetInstance->IsVisible())
	{
		InteractionWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ADetectivePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (SVirtualJoystick::ShouldDisplayTouchInterface() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogGameR, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
	if (hudwidget)
	{
		aimhud = CreateWidget<UUserWidget>(this, hudwidget);
	}

	if (aimhud)
	{
		aimhud->AddToViewport(-1);
	}


	if (InteractionWidgetClass)
	{
		InteractionWidgetInstance = CreateWidget<UInteractionWidget>(this, InteractionWidgetClass);
		if (InteractionWidgetInstance)
		{
			InteractionWidgetInstance->AddToViewport();
			InteractionWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create InteractionWidgetInstance."));
		}
	}

}

void ADetectivePlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);


}

void ADetectivePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!SVirtualJoystick::ShouldDisplayTouchInterface())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
			
		}

		
	}
}

void ADetectivePlayerController::RequestShowActorWidget_Implementation(TSubclassOf<UUserWidget> WidgetClass)
{
	// 1. 혹시 이미 다른 위젯이 열려있다면, 먼저 닫습니다.
	if (CurrentActorWidgetInstance && CurrentActorWidgetInstance->IsInViewport())
	{
		CurrentActorWidgetInstance->RemoveFromParent();
		CurrentActorWidgetInstance = nullptr;
	}

	// 2. 띄워달라고 요청받은 '클래스'가 유효한지 확인
	if (WidgetClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("RequestShowActorWidget: 띄울 위젯 클래스가 Null입니다."));
		return;
	}
	
	CurrentActorWidgetInstance = CreateWidget<UUserWidget>(this, WidgetClass);

	if (CurrentActorWidgetInstance)
	{
		CurrentActorWidgetInstance->AddToViewport();

		// 5. Change InputMode
		bShowMouseCursor = true;
		
		ACharacter* MyCharacter = Cast<ACharacter>(GetPawn());
		UCharacterMovementComponent* MoveComp = MyCharacter->GetCharacterMovement();
		
		if (MoveComp)
		{
			MoveComp->SetMovementMode(EMovementMode::MOVE_None);
		}
		
		SetInputMode(FInputModeUIOnly()); // or FInputModeGameAndUI()
	}	
}

void ADetectivePlayerController::RequestHideActorWidget_Implementation()
{
	if (CurrentActorWidgetInstance && CurrentActorWidgetInstance->IsInViewport())
	{
		CurrentActorWidgetInstance->RemoveFromParent();
		CurrentActorWidgetInstance = nullptr;
	}
	
	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly());

	ACharacter* MyCharacter = Cast<ACharacter>(GetPawn());
	UCharacterMovementComponent* MoveComp = MyCharacter->GetCharacterMovement();
		
	if (MoveComp)
	{
		MoveComp->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}

class UUserWidget* ADetectivePlayerController::GetCurrentWidget_Implementation()
{
	return CurrentActorWidgetInstance;
}
