// Fill out your copyright notice in the Description page of Project Settings.


#include "Env/PlayerTeleportActor.h"

// Sets default values
APlayerTeleportActor::APlayerTeleportActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerTeleportActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerTeleportActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

