// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/Env/ViewableUI.h"
#include "Common/BaseWidget.h"
#include "ViewableActorUI.generated.h"

class UItemData;
/**
 * 
 */
UCLASS()
class GAMER_API UViewableActorUI : public UBaseWidget, public IViewableUI
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> DisplayImg;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> GetButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> DesTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ViewableActorUI")
	class UTexture2D* ShowImg;
	
	virtual void SetUITexture_Implementation(class UTexture2D* texture) override;
	virtual void SetItemData_Implementation(class UUsableItem* itemData) override;
	virtual void SetActor_Implementation(AActor* actor) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<class UUsableItem> ItemData;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<AActor> Actor;

	
	UFUNCTION(BlueprintCallable, Category = "ViewableActorUI")
	virtual void AddToInventory();
	
};
