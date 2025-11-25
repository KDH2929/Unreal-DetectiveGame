// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickupItem.h"
#include "Item/ItemData.h"
#include "Inventory/InventoryComponent.h"
#include "Interface/InventoryInterface.h"

// Sets default values
APickupItem::APickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
    RootComponent = MeshComponent;

    MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void APickupItem::Interaction_Implementation(APawn* Interactor)
{
    if (!ItemData) {
        return;
    }

    UInventoryComponent* Inventory = nullptr;

    if (Interactor->GetClass()->ImplementsInterface(UInventoryInterface::StaticClass()))
    {
        Inventory = IInventoryInterface::Execute_GetInventoryComponent(Interactor);
    }

    
    
    if (!Inventory) {
        return;
    }

    if (Inventory->AddItem(ItemData))
    {
        Destroy();

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan,
                FString::Printf(TEXT("Picked up: %s"), *ItemData->Name.ToString()));
        }
    }
    else
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red,
                TEXT("Inventory Full! Cannot pick up item."));
        }
    }
}

FString APickupItem::GetInteractionText_Implementation(APawn* Interactor) const
{
    if (ItemData)
    {
        return ItemData->InteractionText.ToString();
    }

    return FString(TEXT("None"));
}

// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickupItem::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (MeshComponent && ItemData != nullptr)
    {
        UStaticMesh* ItemMesh = ItemData->Mesh.Get();

        if (ItemMesh)
        {
            MeshComponent->SetStaticMesh(ItemMesh);
        }
        else
        {
            MeshComponent->SetStaticMesh(nullptr);
        }
    }

    else if (MeshComponent)
    {
        MeshComponent->SetStaticMesh(nullptr);
    }
}

// Called every frame
void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

