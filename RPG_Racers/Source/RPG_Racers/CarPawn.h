// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Item_A.h"
#include "InventoryComponent.h"
#include "CarMovementComponent.h"
#include "Store_A.h"
#include "CarPawn.generated.h"

UCLASS()
class RPG_RACERS_API ACarPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACarPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AItem_A* OffensiveWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AStore_A* TheStore = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	//void MoveForward(float Value);
	//void MoveRight(float Value);
	void OpenStore();

};
 