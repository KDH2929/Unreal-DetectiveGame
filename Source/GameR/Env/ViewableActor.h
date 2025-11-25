// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interactable.h"
#include "ViewableActor.generated.h"

UCLASS()
class GAMER_API AViewableActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AViewableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<class UAudioComponent> EngineSoundComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<class USoundBase> OnInteractionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	FString InteractionText = "";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh")
	TObjectPtr<class UStaticMeshComponent> KeyPadMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidget> ViewWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	TObjectPtr<class UUsableItem> UsableItemInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<class UItemData> ItemDatav;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSubclassOf<class UUsableItem> UsableItem;

	virtual void Interaction_Implementation(APawn* Interactor) override;

	virtual FString GetInteractionText_Implementation(APawn* Interactor) const override;

};
