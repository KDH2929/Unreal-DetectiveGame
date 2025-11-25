// Fill out your copyright notice in the Description page of Project Settings.


#include "Env/Door.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"


// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	EngineSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("EngineSoundComponent"));
	EngineSoundComponent->SetupAttachment(RootComponent);
	EngineSoundComponent->SetAutoActivate(false);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::Interaction_Implementation(APawn* Interactor)
{
	if (bIsLock == false)
	{
		if (bIsOpen)
		{
			
			EngineSoundComponent->Stop();
			EngineSoundComponent->SetSound(CloseDoorSound);
			EngineSoundComponent->Play();
			CloseDoor();
			bIsOpen = false;

			OnInteraction.Broadcast(Interactor);
		}
		else
		{
			EngineSoundComponent->Stop();
			EngineSoundComponent->SetSound(OpenDoorSound);
			EngineSoundComponent->Play();
			OpenDoor();
			bIsOpen = true;
		}
	}
	else
	{
		if (LockedSound == nullptr)
			return;
		EngineSoundComponent->Stop();
		EngineSoundComponent->SetSound(LockedSound);
		EngineSoundComponent->Play();
	}
}

FString ADoor::GetInteractionText_Implementation(APawn* Interactor) const
{
	return InteractionText;
}

void ADoor::UnLock_Implementation()
{
	bIsLock = false;
}


