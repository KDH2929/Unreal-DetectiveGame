// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/PlayerHUDInterface.h"
#include "Interface/InteractableTextHUDInterface.h"
#include "GameFramework/PlayerController.h"
#include "DetectivePlayerController.generated.h"

/**
 * 
 */
class UInputMappingContext;
class UUserWidget;
class UInteractionWidget;


UCLASS(abstract)
class GAMER_API ADetectivePlayerController : public APlayerController, public IPlayerHUDInterface, public IInteractableTextHUDInterface
{
	GENERATED_BODY()

public:
	ADetectivePlayerController();

	

protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;
	
	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	/** Mobile controls widget to spawn */
	UPROPERTY(EditAnywhere, Category="Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to the mobile controls widget */
	UPROPERTY(EditAnywhere, Category="I")
	TObjectPtr<UUserWidget> MobileControlsWidget;
	
	UPROPERTY(EditAnywhere, Category="I")
	TSubclassOf<UUserWidget> hudwidget;

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Possessed pawn initialization */
	virtual void OnPossess(APawn* aPawn) override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	// Widget
protected:
	UPROPERTY(VisibleInstanceOnly, Category = "UI")
	TObjectPtr<UUserWidget> CurrentActorWidgetInstance;

	UPROPERTY(VisibleInstanceOnly, Category = "UI")
	TObjectPtr<UUserWidget> aimhud;

	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UInteractionWidget> InteractionWidgetClass;

	UPROPERTY()
	TObjectPtr<UInteractionWidget> InteractionWidgetInstance;
	
	virtual void RequestShowActorWidget_Implementation(TSubclassOf<UUserWidget> WidgetClass) override;
	virtual void RequestHideActorWidget_Implementation() override;
	virtual class UUserWidget* GetCurrentWidget_Implementation() override;


	virtual void ShowInteractionText_Implementation(const FString& Message) override;
	virtual void HideInteractionText_Implementation() override;
	
};
