// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item_A.h"
#include "Blueprint/UserWidget.h"
#include "SlotStruct.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_RACERS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// --------These variables are to declare the player inventory

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString InventoryName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int NumberOfSlots = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FSlotStruct> Inventory;

	// --------These variables will be used to display the inventory

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> InventoryWindowClass;

	UPROPERTY(BlueprintReadOnly)
		UUserWidget* InventoryWindow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FVector2D WindowPosition;

	// --------Functions that can be called in blueprints to add to or remove from inventory

	UFUNCTION(BlueprintCallable)
		void AddItemToInventory(AStat_Item_A* ItemToAdd);

	UFUNCTION(BlueprintCallable)
		void RemoveItemFromInventory(int index);

	void AddToWindow();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool canAccessInventory = true;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	// Initialize the inventory with "Empty" Slots and keep any items that were placed before hitting play.
	void PrepareInventory();
	void RemoveStatsFromPlayer(AStat_Item_A*);
	void AddStatsToPlayer(AStat_Item_A*);
	bool CanAddToInventory(AStat_Item_A* NewItem);
	FSlotStruct GetEmptySlot();
};
