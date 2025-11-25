#include "Interactables/BP_Door.h" 

ABP_Door::ABP_Door()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABP_Door::BeginPlay()
{
	Super::BeginPlay();
}

void ABP_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABP_Door::Interaction_Implementation(APawn* Interactor)
{
	OnInteraction();
}