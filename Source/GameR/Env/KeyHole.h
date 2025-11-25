// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interactable.h"
#include "KeyHole.generated.h"

UCLASS()
class GAMER_API AKeyHole : public AActor, public IInteractable 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeyHole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key")
	FString TrueVale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Key Pad")
	TObjectPtr<AActor> LockedActor;
	
	virtual void Interaction_Implementation(APawn* Interactor) override;
	virtual FString GetInteractionText_Implementation(APawn* Interactor) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<class UAudioComponent> EngineSoundComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<class USoundBase> UnLockSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<class USoundBase> UnLockFaultSound;

	UFUNCTION()
	void OpenDoor();
	
};
