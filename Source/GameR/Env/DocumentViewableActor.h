// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Env/ViewableActor.h"
#include "DocumentViewableActor.generated.h"

/**
 * 
 */
UCLASS()
class GAMER_API ADocumentViewableActor : public AViewableActor
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
};
