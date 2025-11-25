// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Env/Door.h"
#include "ExitDoor.generated.h"

/**
 * 
 */
UCLASS()
class GAMER_API AExitDoor : public ADoor
{
	GENERATED_BODY()

protected:
	virtual void Interaction_Implementation(APawn* Interactor) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	FVector TeleportPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	FRotator TeleportRot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	TSubclassOf<class UUserWidget> TeleportWidget;

	FTimerHandle MyTimerHandle;

	TObjectPtr<APawn> Player;

	TObjectPtr<class UUserWidget> ui;

	void Teleport_Timer();
	void Teleport();
};
