// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionWidget.h"
#include "Components/TextBlock.h"

void UInteractionWidget::SetInteractionText(const FText& NewText)
{
    if (InteractionText)
    {
        InteractionText->SetText(NewText);
    }
}