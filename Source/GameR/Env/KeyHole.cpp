// Fill out your copyright notice in the Description page of Project Settings.


#include "Env/KeyHole.h"
#include "Interface/Item/UseKey.h"
#include "Interface/Env/LockedActor.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

// Sets default values
AKeyHole::AKeyHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	EngineSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("EngineSoundComponent"));
	EngineSoundComponent->SetupAttachment(RootComponent);
	EngineSoundComponent->SetAutoActivate(false);

}

// Called when the game starts or when spawned
void AKeyHole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKeyHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKeyHole::Interaction_Implementation(APawn* Interactor)
{
	if (Interactor->GetClass()->ImplementsInterface(UUseKey::StaticClass()))
	{
		FString PlayerKey = IUseKey::Execute_GetKey(Interactor);

		if (PlayerKey == TrueVale)
		{
			EngineSoundComponent->Stop();
			EngineSoundComponent->SetSound(UnLockSound);
			EngineSoundComponent->Play();
			
			OpenDoor();
		}
		else if (PlayerKey != "" )
		{
			EngineSoundComponent->Stop();
			EngineSoundComponent->SetSound(UnLockFaultSound);
			EngineSoundComponent->Play();
		}
	}
}

FString AKeyHole::GetInteractionText_Implementation(APawn* Interactor) const
{
	return FString("key hole");
}

void AKeyHole::OpenDoor()
{
	if (LockedActor == nullptr)
		return;
	

	if (LockedActor->GetClass()->ImplementsInterface(ULockedActor::StaticClass()))
	{
		ILockedActor::Execute_UnLock(LockedActor);
	}
}

