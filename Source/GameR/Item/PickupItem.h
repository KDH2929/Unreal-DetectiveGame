// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interactable.h"
#include "PickupItem.generated.h"

class UItemData;
class UWidgetComponent;

UCLASS()
class GAMER_API APickupItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupItem();

	virtual void Interaction_Implementation(APawn* Interactor) override;
	virtual FString GetInteractionText_Implementation(APawn* Interactor) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UItemData> ItemData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
};
