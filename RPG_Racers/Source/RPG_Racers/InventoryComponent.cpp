// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "SlotStruct.h"
#include "Store_A.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	UE_LOG(LogTemp, Warning, TEXT("Test"));
	PrepareInventory();
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::PrepareInventory()
{
	auto temp = Inventory;
	Inventory.Init(FSlotStruct::FSlotStruct(), NumberOfSlots);

	for (int i = 0; i < NumberOfSlots; i++)
	{
		if (temp.IsValidIndex(i))
			Inventory[i] = temp[i];
	}
}

bool UInventoryComponent::CanAddToInventory(AItem_A* NewItem)
{
	// This for-loop will prevent the player from getting duplicate items.
	for (int i = 0; i < NumberOfSlots; i++)
	{
		if (Inventory[i].Item->ItemStructure.ID == NewItem->ItemStructure.ID)
			return false;
	}

	// This for-loop will look for an "Empty" slot in the Inventory array and place the new item
	for (int i = 0; i < NumberOfSlots; i++)
	{
		auto EmptySlot = FSlotStruct::FSlotStruct();

		if (Inventory[i].Item->ItemStructure.ID == EmptySlot.Item->ItemStructure.ID)
		{
			EmptySlot.Item = NewItem;
			
			switch (NewItem->ItemStructure.TypeOfItem)
			{
				case ItemType::Attack:
					EmptySlot.Color = FColor::Red;
					break;
				case ItemType::Defense:
					EmptySlot.Color = FColor::Blue;
					break;
				case ItemType::OffensiveWeapon:
					EmptySlot.Color = FColor::Yellow;
					break;
				default:
					EmptySlot.Color = FColor::White;
					break;
			}

			Inventory[i] = EmptySlot;
			AddToWindow();
			return true;
		}
	}

	return false;
}

void UInventoryComponent::AddToWindow()
{
	if (!InventoryWindowClass) { return; }

	if (InventoryWindow && InventoryWindow->IsInViewport())
	{
		InventoryWindow->RemoveFromViewport();
	}

	InventoryWindow = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), InventoryWindowClass);

	if (!InventoryWindow) { return; }

	InventoryWindow->SetAlignmentInViewport(FVector2D(.5, .5));
	InventoryWindow->SetPositionInViewport(WindowPosition);
	InventoryWindow->SetAnchorsInViewport(FAnchors(.5, .5, .5, .5));

	InventoryWindow->AddToViewport();
}

FSlotStruct UInventoryComponent::GetEmptySlot()
{
	return FSlotStruct::FSlotStruct();
}