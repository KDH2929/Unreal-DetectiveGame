// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GameRCharacter.h"
#include "Interface/Item/UseKey.h"
#include "Interface/InventoryInterface.h"
#include "Interface/HandLightInterface.h"
#include "DetectiveCharacter.generated.h"

/**
 * 
 */
UCLASS(abstract)
class GAMER_API ADetectiveCharacter : public AGameRCharacter, public IUseKey, public IInventoryInterface, public IHandLightInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	class USpotLightComponent* SpotLight;

// Input
protected:
	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* InventoryAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* LightOnAction;

	

// SprintParameter
protected:
	/** If true, we're sprinting */
	bool bSprinting = false;

	/** If true, we're recovering stamina */
	bool bRecovering = false;

	/** Default walk speed when not sprinting or recovering */
	UPROPERTY(EditAnywhere, Category="Walk")
	float WalkSpeed = 250.0f;

	/** Time interval for sprinting stamina ticks */
	UPROPERTY(EditAnywhere, Category="Sprint", meta = (ClampMin = 0, ClampMax = 1, Units = "s"))
	float SprintFixedTickTime = 0.03333f;

	/** Sprint stamina amount. Maxes at SprintTime */
	float SprintMeter = 0.0f;

	/** How long we can sprint for, in seconds */
	UPROPERTY(EditAnywhere, Category="Sprint", meta = (ClampMin = 0, ClampMax = 10, Units = "s"))
	float SprintTime = 3.0f;

	/** Walk speed while sprinting */
	UPROPERTY(EditAnywhere, Category="Sprint", meta = (ClampMin = 0, ClampMax = 10, Units = "cm/s"))
	float SprintSpeed = 600.0f;

	/** Walk speed while recovering stamina */
	UPROPERTY(EditAnywhere, Category="Recovery", meta = (ClampMin = 0, ClampMax = 10, Units = "cm/s"))
	float RecoveringWalkSpeed = 150.0f;

	/** Time it takes for the sprint meter to recover */
	UPROPERTY(EditAnywhere, Category="Recovery", meta = (ClampMin = 0, ClampMax = 10, Units = "s"))
	float RecoveryTime = 0.0f;

	/** Sprint tick timer */
	FTimerHandle SprintTimer;

protected:
	ADetectiveCharacter();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	/** Gameplay cleanup */
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	/** Set up input action bindings */
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

protected:
	/** Starts sprinting behavior */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void DoStartSprint();

	/** Stops sprinting behavior */
	UFUNCTION(BlueprintCallable, Category="Input")
	void DoEndSprint();

	UFUNCTION(BlueprintCallable, Category="Input")
	void Interact();

	/** Called while sprinting at a fixed time interval */
	void SprintFixedTick();

	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void OpenInventory();

	virtual void InventoryOpen_Implementation() override;

	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void LightOn();
	
// Camera Item
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Photo Capture")
	TObjectPtr<class UPhotoCaptureComponent> PhotoCaptureComponent;

	UFUNCTION(BlueprintCallable, Category="Photo Capture")
	void TakePhoto();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Photo Capture")
	TObjectPtr<class UTexture2D> TestTexture;

	// Key
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Key")
	FString CurrentKey = "";
	
	virtual void SetKey_Implementation(const FString& Key) override;
	virtual FString GetKey_Implementation() override;

	// Inventory
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<class UInventoryComponent> InventoryComponent;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<class UInventoryWidget> InventoryWidgetClass;

	virtual class UInventoryComponent* GetInventoryComponent_Implementation() const override;
	
	virtual void CloseInventory();

	// Interaction
protected:
	void TraceForInteractable();
	
	UPROPERTY()
	AActor* CurrentFocusedActor = nullptr;

	UPROPERTY()
	bool bIsLgiht = false;

	virtual void SetLight_Implementation() override;

	// pade in pade out
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pade")
	float FadeDuration = 0.5f;

	void StartFade();
	
	
};
