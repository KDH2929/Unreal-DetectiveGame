// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interactable.h"
#include "Interface/Env/LockedActor.h"
#include "Door.generated.h"

UCLASS()
class GAMER_API ADoor : public AActor, public IInteractable, public ILockedActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 
protected:
	virtual void Interaction_Implementation(APawn* Interactor) override;
	
	virtual FString GetInteractionText_Implementation(APawn* Interactor) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	FString InteractionText = "Door";
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	bool bIsOpen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	bool bIsLock = false;

	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void OpenDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void CloseDoor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<class UAudioComponent> EngineSoundComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<class USoundBase> OpenDoorSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<class USoundBase> CloseDoorSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<class USoundBase> LockedSound;

	virtual void UnLock_Implementation() override;
	

};
