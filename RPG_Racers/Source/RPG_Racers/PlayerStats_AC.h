// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OffensiveWeapon_Item_A.h"
#include "Checkpoint_A.h"
#include "PlayerCheckpoints_A.h"
#include "PlayerStats_AC.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_RACERS_API UPlayerStats_AC : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerStats_AC();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AttackPower = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DefensiveProtections = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DrivingSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float StartingMaxDrivingForce = 10000;

	UFUNCTION(BlueprintCallable)
		bool ReceiveDamage(float DamageTaken);

	UFUNCTION(BlueprintCallable)
		int UpdateCheckpoint(int checkpointOn);

	UFUNCTION(BlueprintCallable)
		void Respawn();

	UPROPERTY(EditAnywhere)
		ACheckpoint_A* TemporaryRespawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CheckpointToGo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APlayerCheckpoints_A* LevelCheckpoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentLap = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentPlace = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float distanceToNextCheckpoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isImmune = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool isNPC = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool canMove = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool isDead = false;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	void PlayerDead();

	TArray<AActor*> allRacers;
};
