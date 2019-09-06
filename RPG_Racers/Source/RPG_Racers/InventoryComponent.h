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
		int NumberOfSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FSlotStruct> Inventory;

	// --------These variables will be used to display the inventory

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> InventoryWindowClass;

	UPROPERTY(BlueprintReadOnly)
		UUserWidget* InventoryWindow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FVector2D WindowPosition;

	// --------Functions that can be called in blueprints

	UFUNCTION(BlueprintCallable)
		bool CanAddToInventory(AItem_A* NewItem);

	UFUNCTION(BlueprintCallable)
		void AddToWindow();
		
	UFUNCTION(BlueprintCallable)
		FSlotStruct GetEmptySlot();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	void PrepareInventory();
		
};
