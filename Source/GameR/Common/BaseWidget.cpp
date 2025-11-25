// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/BaseWidget.h"

#include <ThirdParty/ShaderConductor/ShaderConductor/External/SPIRV-Headers/include/spirv/unified1/spirv.h>

#include "GameFramework/PlayerController.h"
#include "Interface/PlayerHUDInterface.h"
#include "Components/BackgroundBlur.h"
#include "Styling/SlateBrush.h"
#include "Components/Image.h"
#include "Components/Button.h"


void UBaseWidget::CloseWidget()
{
	APlayerController* PlayerController = GetOwningPlayer();
	
	if (PlayerController->GetClass()->ImplementsInterface(UPlayerHUDInterface::StaticClass()))
	{
		IPlayerHUDInterface::Execute_RequestHideActorWidget(PlayerController);
	}
}

void UBaseWidget::OnCloseButtonClicked()
{
	CloseWidget();
}

void UBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (BackgroundBlur)
	{
		BackgroundBlur->SetBlurStrength(1.6f);
	}

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UBaseWidget::OnCloseButtonClicked);
		CloseButton->SetBackgroundColor(FLinearColor(0,0,0,0));
	}

	if (BackGroundImg)
	{
		FSlateBrush CurrentBrush = BackGroundImg->GetBrush();
		CurrentBrush.TintColor = FSlateColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.4f));
		BackGroundImg->SetBrush(CurrentBrush);
	}
}
