// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DetectiveCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Components/SpotLightComponent.h"
#include "Item/PhotoCapture/PhotoCaptureComponent.h"
#include "Engine/Texture2D.h"
#include "Interface/Interactable.h"
#include "Interface/InteractableTextHUDInterface.h"
#include "Interface/PlayerHUDInterface.h"
#include "Inventory/InventoryWidget.h"
#include "Inventory/InventoryComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/PlayerController.h"



ADetectiveCharacter::ADetectiveCharacter()
{
	// create the spotlight
	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(GetFirstPersonCameraComponent());

	SpotLight->SetRelativeLocationAndRotation(FVector(30.0f, 17.5f, -5.0f), FRotator(-18.6f, -1.3f, 5.26f));
	SpotLight->Intensity = 0.5;
	SpotLight->SetIntensityUnits(ELightUnits::Lumens);
	SpotLight->AttenuationRadius = 1050.0f;
	SpotLight->InnerConeAngle = 18.7f;
	SpotLight->OuterConeAngle = 45.24f;

	SpotLight->SetVisibility(false);

	PhotoCaptureComponent = CreateDefaultSubobject<UPhotoCaptureComponent>(TEXT("PhotoCapture"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}


void ADetectiveCharacter::BeginPlay()
{
	Super::BeginPlay();

	// initialize sprint meter to max
	SprintMeter = SprintTime;

	// Initialize the walk speed
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	// start the sprint tick timer
	GetWorld()->GetTimerManager().SetTimer(SprintTimer, this, &ADetectiveCharacter::SprintFixedTick, SprintFixedTickTime, true);
}

void ADetectiveCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TraceForInteractable();
}

void ADetectiveCharacter::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// clear the sprint timer
	GetWorld()->GetTimerManager().ClearTimer(SprintTimer);
}

void ADetectiveCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	{
		// Set up action bindings
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			// Sprinting
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ADetectiveCharacter::DoStartSprint);
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ADetectiveCharacter::DoEndSprint);
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ADetectiveCharacter::Interact);
			EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &ADetectiveCharacter::OpenInventory);
			
			EnhancedInputComponent->BindAction(LightOnAction, ETriggerEvent::Started, this, &ADetectiveCharacter::LightOn);
		}
	}
}

void ADetectiveCharacter::DoStartSprint()
{
	// set the sprinting flag
	bSprinting = true;

	// are we out of recovery mode?
	if (!bRecovering)
	{
		// set the sprint walk speed
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		
	}
}

void ADetectiveCharacter::DoEndSprint()
{
	// set the sprinting flag
	bSprinting = false;

	// are we out of recovery mode?
	if (!bRecovering)
	{
		// set the default walk speed
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		
	}
}

void ADetectiveCharacter::Interact()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (!PlayerController) {
		return;
	}


    FVector CameraLocation;
    FRotator CameraRotation;
    PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

    const float TraceDistance = 500.f;

    FVector ForwardVector = CameraRotation.Vector();
    FVector TraceEnd = CameraLocation + (ForwardVector * TraceDistance);

    FHitResult HitResult;
    FCollisionQueryParams TraceParams(FName(TEXT("LineTrace")), true, this);

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        CameraLocation,
        TraceEnd,
        ECC_GameTraceChannel2,
        TraceParams
    );

	/*
    DrawDebugLine(
        GetWorld(),
        CameraLocation,
        TraceEnd,
        bHit ? FColor::Green : FColor::Red,
        false,
        1.0f,
        0,
        5.0f 
    );
	*/


    if (bHit)
    {
        AActor* HitActor = HitResult.GetActor();

        if (HitActor)
        {
            if (HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
            {
                IInteractable::Execute_Interaction(HitActor,this);
                
                FString ActorName = HitActor->GetName();
                return; 
            }

            FString ActorName = HitActor->GetName();
        }
    }
    else
    {

    }
}


void ADetectiveCharacter::SprintFixedTick()
{
	// are we out of recovery, still have stamina and are moving faster than our walk speed?
	if (bSprinting && !bRecovering && GetVelocity().Length() > WalkSpeed)
	{

		// do we still have meter to burn?
		if (SprintMeter > 0.0f)
		{
			// update the sprint meter
			SprintMeter = FMath::Max(SprintMeter - SprintFixedTickTime, 0.0f);

			// have we run out of stamina?
			if (SprintMeter <= 0.0f)
			{
				// raise the recovering flag
				bRecovering = true;

				// set the recovering walk speed
				GetCharacterMovement()->MaxWalkSpeed = RecoveringWalkSpeed;
			}
		}
		
	} else {

		// recover stamina
		SprintMeter = FMath::Min(SprintMeter + SprintFixedTickTime, SprintTime);

		if (SprintMeter >= SprintTime)
		{
			// lower the recovering flag
			bRecovering = false;

			// set the walk or sprint speed depending on whether the sprint button is down
			GetCharacterMovement()->MaxWalkSpeed = bSprinting ? SprintSpeed : WalkSpeed;
			
		}

	}
}


void ADetectiveCharacter::TakePhoto()
{
	TestTexture = PhotoCaptureComponent->GetCurrentTexture();
}

void ADetectiveCharacter::SetKey_Implementation(const FString& Key)
{
	this->CurrentKey = Key;
}

FString ADetectiveCharacter::GetKey_Implementation()
{
	return CurrentKey;
}

void ADetectiveCharacter::OpenInventory()
{
	if (InventoryWidgetClass == nullptr)
		return;
    
	AController* PlayerController = GetController();
    
	if (PlayerController->GetClass()->ImplementsInterface(UPlayerHUDInterface::StaticClass()))
	{
		IPlayerHUDInterface::Execute_RequestShowActorWidget(PlayerController, InventoryWidgetClass);
		UUserWidget* CurrentWidget = IPlayerHUDInterface::Execute_GetCurrentWidget(PlayerController);

		if (CurrentWidget)
		{
			if (UInventoryWidget* InventoryWidget = Cast<UInventoryWidget>(CurrentWidget))
			{
				InventoryWidget->BindInventory(InventoryComponent);
			}
		}
	}
}

void ADetectiveCharacter::InventoryOpen_Implementation()
{
	IInventoryInterface::InventoryOpen_Implementation();
}


void ADetectiveCharacter::LightOn()
{
	if (bIsLgiht)
	{
		if (SpotLight->IsVisible())
			SpotLight->SetVisibility(false);
		else
		{
			SpotLight->SetVisibility(true);
		}
	}
		
}

class UInventoryComponent* ADetectiveCharacter::GetInventoryComponent_Implementation() const
{
	return InventoryComponent.Get();
}	

void ADetectiveCharacter::CloseInventory()
{
	if (InventoryWidgetClass == nullptr)
		return;
    
	AController* PlayerController = GetController();
    
	if (PlayerController->GetClass()->ImplementsInterface(UPlayerHUDInterface::StaticClass()))
	{
		IPlayerHUDInterface::Execute_RequestHideActorWidget(PlayerController);
	}
}

void ADetectiveCharacter::TraceForInteractable()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    
    if (PlayerController == nullptr)
    {
        return;
    }

    FVector CameraLocation;
    FRotator CameraRotation;
    PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

    const float TraceDistance = 500.0f;
    FVector TraceEnd = CameraLocation + (CameraRotation.Vector() * TraceDistance);

    FHitResult HitResult;
    FCollisionQueryParams TraceParams(FName(TEXT("InteractTrace")), true, this);

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        CameraLocation,
        TraceEnd,
        ECC_GameTraceChannel2,
        TraceParams
    );

    AActor* HitActor = bHit ? HitResult.GetActor() : nullptr;

	/*
    DrawDebugLine(
        GetWorld(),
        CameraLocation,
        TraceEnd,
        bHit ? FColor::Green : FColor::Red,
        false,
        0.0f,
        0,
        1.5f
    );
    */
	

    // 이전 포커스된 액터와 다르면 상태 갱신
    if (CurrentFocusedActor != HitActor)
    {
        if (HitActor == nullptr)
        {
            CurrentFocusedActor = HitActor;

            if (PlayerController->GetClass()->ImplementsInterface(UInteractableTextHUDInterface::StaticClass()))
            {
                IInteractableTextHUDInterface::Execute_HideInteractionText(PlayerController);
            }

            return;
        }
        
        // 새 액터 UI 보이기
        if (HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
        {
            FString InteractionMessage = IInteractable::Execute_GetInteractionText(HitActor, this);

            if (PlayerController->GetClass()->ImplementsInterface(UInteractableTextHUDInterface::StaticClass()))
            {
                IInteractableTextHUDInterface::Execute_ShowInteractionText(PlayerController, InteractionMessage);
            }
        }
        else
        {

            if (PlayerController->GetClass()->ImplementsInterface(UInteractableTextHUDInterface::StaticClass()))
            {
                IInteractableTextHUDInterface::Execute_HideInteractionText(PlayerController);
            }
            
        }

        CurrentFocusedActor = HitActor;
    }
}

void ADetectiveCharacter::SetLight_Implementation()
{
	bIsLgiht = true;
}

void ADetectiveCharacter::StartFade()
{
	APlayerController* MyController = Cast<APlayerController>(GetController());
	
	APlayerCameraManager* PCM = MyController->PlayerCameraManager;

	PCM->StartCameraFade(
		0.0f,               
		1.0f,               
		FadeDuration,       
		FLinearColor::Black,
		true,               
		true                
	);
}
