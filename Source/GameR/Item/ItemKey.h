// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/UsableItem.h"
#include "ItemKey.generated.h"

/**
 * 
 */
UCLASS()
class GAMER_API UItemKey : public UUsableItem
{
	GENERATED_BODY()

public:
	virtual void SetItemData(UItemData* NewData) override;

protected:
	virtual void Use(APawn* Interactor) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FString TrueValue = "";

	
	
};
