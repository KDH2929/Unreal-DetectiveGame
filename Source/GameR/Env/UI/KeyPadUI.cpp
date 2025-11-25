// Fill out your copyright notice in the Description page of Project Settings.


#include "Env/UI/KeyPadUI.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerController.h"
#include "Interface/PlayerHUDInterface.h"


FKeyValueCorrect& UKeyPadUI::GetCorrectKeyDelegate()
{
	return CorrectkKeyValue;
}

void UKeyPadUI::SetKeyData(FString data)
{
	
	this->TrueValue = data;

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TrueValue);
}

void UKeyPadUI::MatchKeyData()
{
	bool bIsCorrect = (keyValue == TrueValue);
	
	if (bIsCorrect)
	{
		
		CorrectkKeyValue.Broadcast();
		
		CloseWidget();
	}
	else
	{
		ClearKeyData();
	}
}

void UKeyPadUI::AppendKey(FString Key)
{
	const int MaxKeyLength = 4;
	
	if (keyValue.Len() >= MaxKeyLength)
	{
		return;
	}

	keyValue.Append(Key);
	
	if (InputDisplay)
	{
		InputDisplay->SetText(FText::FromString(keyValue));
	}
}

void UKeyPadUI::ClearKeyData()
{
	keyValue.Empty();
    
	if (InputDisplay)
	{
		InputDisplay->SetText(FText::FromString(keyValue));
	}
}

void UKeyPadUI::Backspace()
{
	keyValue = keyValue.LeftChop(1);
    
	if (InputDisplay)
	{
		InputDisplay->SetText(FText::FromString(keyValue));
	}
}


void UKeyPadUI::NativeConstruct()
{
	Super::NativeConstruct();

	ClearKeyData();
}
