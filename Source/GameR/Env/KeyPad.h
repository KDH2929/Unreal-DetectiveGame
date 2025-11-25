// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/Interactable.h"
#include "GameFramework/Actor.h"
#include "KeyPad.generated.h"

class UUserWidget;
UCLASS()
class GAMER_API AKeyPad : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeyPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Key Pad
public:

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Key Pad")
	FString TrueVale;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Key Pad")
	TObjectPtr<class UStaticMeshComponent> KeyPadMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Key Pad")
	TObjectPtr<AActor> LockedActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Key Pad")
	TSubclassOf<UUserWidget> KeyPadUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Key Pad")
	FString Des = "Key Pad";

	UFUNCTION()
	virtual void Interaction_Implementation(APawn* Interactor) override;

	virtual FString GetInteractionText_Implementation(APawn* Interactor) const override;

	UFUNCTION()
	void OpenDoor();

	

	

};
