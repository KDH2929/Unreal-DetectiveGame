// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemData.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EItemType : uint8
{
	IT_Key      UMETA(DisplayName = "Key"),
	IT_Document UMETA(DisplayName = "Document"),
	IT_Misc     UMETA(DisplayName = "Miscellaneous")
};

UENUM(BlueprintType)
enum class InventoryType : uint8
{
	IT_Usable      UMETA(DisplayName = "Usable"),
	IT_NotUsable   UMETA(DisplayName = "NotUsable"),

};

UCLASS(Blueprintable)
class GAMER_API UItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data", meta = (MultiLine = "true"))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data", meta = (MultiLine = "true"))
	FText InteractionText;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	TObjectPtr<UTexture2D> ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	InventoryType InventoryType;

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("ItemData", GetFName()); 
	}
	
	
};
