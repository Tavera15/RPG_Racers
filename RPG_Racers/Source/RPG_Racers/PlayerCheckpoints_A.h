// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint_A.h"
#include "PlayerCheckpoints_A.generated.h"

UCLASS()
class RPG_RACERS_API APlayerCheckpoints_A : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerCheckpoints_A();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ACheckpoint_A*> LevelCheckpoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool canRace = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float timeToStart = 30.0f;

	void RacePlacement();
	void CalculateDistances();

	TArray<AActor*> allRacers;

	float GetDistanceToCheckpoint(AActor* Racer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int heighestCheckpointIndex = -1;
	int heighestLap = -1;
};
