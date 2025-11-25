#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interactable.h"
#include "BP_Door.generated.h"

UCLASS()
class GAMER_API ABP_Door : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	ABP_Door();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
	void OnInteraction();

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void Interaction_Implementation(APawn* Interactor) override;
};