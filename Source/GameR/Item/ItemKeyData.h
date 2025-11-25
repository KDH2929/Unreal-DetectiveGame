// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemData.h"
#include "ItemKeyData.generated.h"

/**
 * 
 */
UCLASS()
class GAMER_API UItemKeyData : public UItemData
{
	GENERATED_BODY()

public:
	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("ItemData", GetFName());
	}
	
	UItemKeyData()
	{
		ItemType = EItemType::IT_Key;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Key Data")
	FString keycode;
	
};
