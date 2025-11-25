// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemData.h"
#include "ItemDocumentData.generated.h"

/**
 * 
 */
UCLASS()
class GAMER_API UItemDocumentData : public UItemData
{
	GENERATED_BODY()

public:
	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("ItemData", GetFName());
	}
	
	UItemDocumentData()
	{
		ItemType = EItemType::IT_Document;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item, meta = (MultiLine = "true"))
	TArray<FText> DocumentContent;
	
};
