// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhotoCaptureComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPhotoCapturedDelegate);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMER_API UPhotoCaptureComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPhotoCaptureComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void InitializeComponent() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// Scene Capture
public:
	void InitToAttechCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Photo Capture")
	TObjectPtr<class USceneCaptureComponent2D> SceneCapture = nullptr;
	
	FOnPhotoCapturedDelegate OnPhotoCapture;
	
	UTexture2D* GetCurrentTexture();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Photo Capture")
	TObjectPtr<class UTextureRenderTarget2D> TextureTarget;
};
