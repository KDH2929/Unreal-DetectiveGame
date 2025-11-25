// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PhotoCapture/PhotoCaptureComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/Texture2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/PostProcessVolume.h"

// Sets default values for this component's properties
UPhotoCaptureComponent::UPhotoCaptureComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	//SceneCapture->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
	
}


// Called when the game starts
void UPhotoCaptureComponent::BeginPlay()
{
	Super::BeginPlay();

	/*
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC || !PC->PlayerCameraManager || !SceneCapture) return;
	
	FPostProcessSettings PlayerPPSettings = PC->PlayerCameraManager->GetCameraCachePOV().PostProcessSettings;
	
	SceneCapture->PostProcessSettings = PlayerPPSettings;
	*/
	
	//SceneCapture->TextureTarget = TextureTarget;
	//SceneCapture->bCaptureEveryFrame = false;
	//SceneCapture->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
}

void UPhotoCaptureComponent::InitializeComponent()
{
	Super::InitializeComponent();
}


// Called every frame
void UPhotoCaptureComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPhotoCaptureComponent::InitToAttechCharacter()
{
	
}

UTexture2D* ConvertRenderTargetToTexture2D(UTextureRenderTarget2D* InRenderTarget, UObject* Outer, FString NewTexName = FString(TEXT(" ")), EObjectFlags Flags = RF_NoFlags, EConstructTextureFlags InFlags = CTF_Default)
{
	if (!InRenderTarget)
	{
		UE_LOG(LogTemp, Error, TEXT("ConvertRenderTargetToTexture2D: InRenderTarget is null."));
		return nullptr;
	}

	UTexture2D* NewTexture = InRenderTarget->ConstructTexture2D(
		Outer, 
		NewTexName, 
		Flags, 
		InFlags
	);

	if (NewTexture)
	{
		NewTexture->UpdateResource();
		return NewTexture;
	}

	UE_LOG(LogTemp, Error, TEXT("ConvertRenderTargetToTexture2D: Failed to construct Texture2D."));
	return nullptr;
}

UTexture2D* UPhotoCaptureComponent::GetCurrentTexture()
{
	if (TextureTarget)
	{
		SceneCapture->CaptureScene();

		UTexture2D* texture = ConvertRenderTargetToTexture2D(SceneCapture->TextureTarget, this, "Screen Photo");
		UE_LOG(LogTemp, Display, TEXT("Take Photo Texture"));
	
		OnPhotoCapture.Broadcast();

		return texture;
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No Texture Target"));
	}
	
	
	return nullptr;
}

