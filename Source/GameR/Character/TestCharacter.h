// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GameRCharacter.h"
#include "TestCharacter.generated.h"

class UInventoryComponent;
class UInventoryWidget;

/**
 * 
 */
UCLASS()
class GAMER_API ATestCharacter : public AGameRCharacter
{
	GENERATED_BODY()

public:
	ATestCharacter();
	
	UInventoryComponent* GetInventoryComponent() const;

protected:

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoInteract();

	virtual void OpenInventory();
	virtual void CloseInventory();

	void TraceForInteractable();



	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

protected:

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* InteractAction;


	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* InventoryAction;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<UInventoryComponent> InventoryComponent;


private:
	// 현재 보고 있는 상호작용 대상
	UPROPERTY()
	AActor* CurrentFocusedActor = nullptr;

};
