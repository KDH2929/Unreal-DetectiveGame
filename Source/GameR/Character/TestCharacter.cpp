// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Inventory/InventoryComponent.h"
#include "Inventory/InventoryWidget.h"
#include "Interface/Interactable.h"
#include "Interface/PlayerHUDInterface.h"
#include "Interface/InteractableTextHUDInterface.h"
#include "GameR.h"


ATestCharacter::ATestCharacter() 
{
    PrimaryActorTick.bCanEverTick = true;

    InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}

UInventoryComponent* ATestCharacter::GetInventoryComponent() const
{
    return InventoryComponent.Get();
}

void ATestCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ATestCharacter::DoInteract);
        EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &ATestCharacter::OpenInventory);
	}
	else
	{
		UE_LOG(LogGameR, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATestCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    TraceForInteractable();     // 매 프레임 상호작용 UI 표시용 라인트레이스 호출
}

void ATestCharacter::DoInteract()
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Interact!"));

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
    FCollisionQueryParams TraceParams(FName(TEXT("LineTrace")), true, this); // 'this'를 통해 자기 자신은 무시

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        CameraLocation,
        TraceEnd,
        ECC_Visibility, // Visible한 모든 물체를 검사
        TraceParams
    );


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


    if (bHit)
    {
        AActor* HitActor = HitResult.GetActor();

        if (HitActor)
        {
            if (HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
            {
                IInteractable::Execute_Interaction(HitActor,this);
                
                FString ActorName = HitActor->GetName();
                if (GEngine)
                {
                    GEngine->AddOnScreenDebugMessage(
                        -1, 3.0f, FColor::Yellow,
                        FString::Printf(TEXT("Interacting with: %s"), *ActorName)
                    );
                }

                return; 
            }

            FString ActorName = HitActor->GetName();
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(
                    -1, 1.0f, FColor::Cyan,
                    FString::Printf(TEXT("Hit: %s (Not Interactable)"), *ActorName)
                );
            }
        }
    }
    else
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("No Hit"));
        }
    }
}

void ATestCharacter::OpenInventory()
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

void ATestCharacter::CloseInventory()
{
    if (InventoryWidgetClass == nullptr)
        return;
    
    AController* PlayerController = GetController();
    
    if (PlayerController->GetClass()->ImplementsInterface(UPlayerHUDInterface::StaticClass()))
    {
        IPlayerHUDInterface::Execute_RequestHideActorWidget(PlayerController);
    }
}

void ATestCharacter::TraceForInteractable()
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
        ECC_Visibility,
        TraceParams
    );

    AActor* HitActor = bHit ? HitResult.GetActor() : nullptr;

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