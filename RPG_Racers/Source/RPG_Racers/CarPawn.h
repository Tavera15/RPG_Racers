// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerStats_AC.h"
#include "OffensiveWeapon_Item_A.h"
#include "InventoryComponent.h"
#include "CarMovementComponent.h"
#include "Checkpoint_A.h"
#include "Store_A.h"
#include "Blueprint/UserWidget.h"
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
		UPlayerStats_AC* PlayerStats = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AOffensiveWeapon_Item_A* OffensiveWeapon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UInventoryComponent* InventoryComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AStore_A* TheStore = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCarMovementComponent* CarMovementComp = nullptr;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> PlayerStatsUIClass;

	UPROPERTY(BlueprintReadOnly)
		UUserWidget* PlayerStatsUI;

	UFUNCTION(BlueprintCallable)
		void MoveForward(float Value);

	UFUNCTION(BlueprintCallable)
		void MoveRight(float Value);

	UFUNCTION(BlueprintCallable)
		void OpenStore();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void OpenRacerStats();
	void UseWeapon();
	FRotator faceDestination;
};
 