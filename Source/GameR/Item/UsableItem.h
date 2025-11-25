// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemData.h"
#include "UsableItem.generated.h"


UCLASS(BlueprintType, Blueprintable)
class GAMER_API UUsableItem : public UObject
{
	GENERATED_BODY()

public:
	UUsableItem();

	virtual void Use(APawn* Interactor);
	
	virtual void SetItemData(UItemData* NewData);
	UItemData* GetItemData() const;
	
	void SetName(const FText& NewName);
	FText GetName() const;

	void SetItemImage(UTexture2D* NewImage);
	UTexture2D* GetItemImage() const;

	void SetDescription(const FText& NewDescription);
	FText GetDescription() const;


protected:
	virtual void PostInitProperties() override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	TObjectPtr<UItemData> ItemData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	FText Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	TObjectPtr<UTexture2D> ItemImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	FText Description;

};
