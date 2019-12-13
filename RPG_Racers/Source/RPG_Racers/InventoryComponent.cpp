// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "SlotStruct.h"
#include "CarPawn.h"
#include "PlayerStats_AC.h"
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

void UInventoryComponent::AddItemToInventory(AStat_Item_A* ItemToAdd, UPlayerStats_AC* RacerStats)
{
	if (!canAccessInventory)
		return;

	if (CanAddToInventory(ItemToAdd, RacerStats))
		AddStatsToPlayer(ItemToAdd, RacerStats);

	if (!RacerStats->isNPC)
		AddToWindow();
}

bool UInventoryComponent::CanAddToInventory(AStat_Item_A* NewItem, UPlayerStats_AC* RacerStats)
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
		auto EmptySlot = GetEmptySlot();

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
			AddStatsToPlayer(Inventory[i].Item, RacerStats);
			return true;
		}
	}

	return false;
}

void UInventoryComponent::RemoveItemFromInventory(int index)
{
	if (!canAccessInventory)
		return;

	auto ItemSlot = Inventory[index];

	if (ItemSlot.Item->ItemStructure.ID == GetEmptySlot().Item->ItemStructure.ID)
		return;

	RemoveStatsFromPlayer(ItemSlot.Item);
	Inventory[index] = GetEmptySlot();
	AddToWindow();
}

void UInventoryComponent::AddStatsToPlayer(AStat_Item_A* ItemToAdd, UPlayerStats_AC* RacerStats)
{
	if (!RacerStats) { return; }

	RacerStats->AttackPower += ItemToAdd->AttackPower;
	RacerStats->DefensiveProtections += ItemToAdd->DefensiveProtections;
	RacerStats->DrivingSpeed += ItemToAdd->DrivingSpeed;
}

void UInventoryComponent::RemoveStatsFromPlayer(AStat_Item_A* ItemToRemove)
{
	auto PlayerStats = Cast<ACarPawn>(GetOwner())->FindComponentByClass<UPlayerStats_AC>();

	if (!PlayerStats) { return; }

	PlayerStats->AttackPower -= ItemToRemove->AttackPower;
	PlayerStats->DefensiveProtections -= ItemToRemove->DefensiveProtections;
	PlayerStats->DrivingSpeed -= ItemToRemove->DrivingSpeed;
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

	InventoryWindow->AddToViewport();
}

FSlotStruct UInventoryComponent::GetEmptySlot()
{
	return FSlotStruct::FSlotStruct();
}


