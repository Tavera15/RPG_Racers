// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCheckpoints_A.h"
#include "PlayerStats_AC.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values
APlayerCheckpoints_A::APlayerCheckpoints_A()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCheckpoints_A::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < LevelCheckpoints.Num(); i++)
	{
		LevelCheckpoints[i]->Index = i;
	}

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Racer", allRacers);
	isWinnerFound = false;
	// Set winner to null
}

// Called every frame
void APlayerCheckpoints_A::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!winner)
	{
		RacePlacement();
		CheckWinner();
	}
	else
	{
		canRace = false;
		isWinnerFound = true;
		//UE_LOG(LogTemp, Warning, TEXT("Winner: %s"), *winner->GetName());
	}
}

void APlayerCheckpoints_A::CheckWinner()
{
	if (!canRace) { return; }

	for (int i = 0; i < allRacers.Num(); i++)
	{
		auto currentRacerStats = allRacers[i]->FindComponentByClass<UPlayerStats_AC>();
		if (currentRacerStats->CurrentLap == lapsToComplete)
		{
			winner = allRacers[i];
			canRace = false;
			return;
		}
	}
}

void APlayerCheckpoints_A::RacePlacement()
{
	// Using the racers, find the heighest lap the race is on.
	int localHeighestLap;

	for (int i = 0; i < allRacers.Num(); i++)
	{
		if (i == 0)
			localHeighestLap = allRacers[i]->FindComponentByClass<UPlayerStats_AC>()->CurrentLap;
		else
			if (allRacers[i]->FindComponentByClass<UPlayerStats_AC>()->CurrentLap > heighestLap)
				localHeighestLap = allRacers[i]->FindComponentByClass<UPlayerStats_AC>()->CurrentLap;
	}

	if (localHeighestLap > heighestLap)
	{
		heighestLap = localHeighestLap;
		heighestCheckpointIndex = 0;
	}

	//UE_LOG(LogTemp, Warning, TEXT("Heighest Lap: %d"), heighestLap);

	// Find the heighest lap
	for (int i = 0; i < allRacers.Num(); i++)
	{
		if (allRacers[i]->FindComponentByClass<UPlayerStats_AC>()->CurrentLap != heighestLap)
			continue;

		if (allRacers[i]->FindComponentByClass<UPlayerStats_AC>()->CurrentLap >= heighestLap && 
			allRacers[i]->FindComponentByClass<UPlayerStats_AC>()->CheckpointToGo > heighestCheckpointIndex)
		{
			heighestCheckpointIndex = allRacers[i]->FindComponentByClass<UPlayerStats_AC>()->CheckpointToGo;
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("Heighest CP: %d"), heighestCheckpointIndex);
	CalculateDistances();
}


void APlayerCheckpoints_A::CalculateDistances()
{
	//UE_LOG(LogTemp, Warning, TEXT("Heighest CP: %d"), heighestCheckpointIndex);

	for (int i = 0; i < allRacers.Num(); i++)
	{
		allRacers[i]->FindComponentByClass<UPlayerStats_AC>()->distanceToNextCheckpoint = GetDistanceToCheckpoint(allRacers[i]);
	}
	
	for (int i = 0; i < allRacers.Num()-1; i++)
	{
		for (int j = i+1; j < allRacers.Num(); j++)
		{
			bool isCloserToDestination = allRacers[j]->FindComponentByClass<UPlayerStats_AC>()->distanceToNextCheckpoint <
				allRacers[i]->FindComponentByClass<UPlayerStats_AC>()->distanceToNextCheckpoint;

			bool isAheadInLaps = allRacers[j]->FindComponentByClass<UPlayerStats_AC>()->CurrentLap >=
				allRacers[i]->FindComponentByClass<UPlayerStats_AC>()->CurrentLap;

			if (isAheadInLaps && isCloserToDestination)
			{
				auto temp = allRacers[j];
				allRacers[j] = allRacers[i];
				allRacers[i] = temp;
			}
		}
	}

	for (int i = 0; i < allRacers.Num(); i++)
	{
		allRacers[i]->FindComponentByClass<UPlayerStats_AC>()->CurrentPlace = i + 1;
	}

}

float APlayerCheckpoints_A::GetDistanceToCheckpoint(AActor* racer)
{
	auto destination = LevelCheckpoints[heighestCheckpointIndex];

	auto copyRacer = racer;
	auto racerStats = copyRacer->FindComponentByClass<UPlayerStats_AC>();
	int racerCPToGo = racer->FindComponentByClass<UPlayerStats_AC>()->CheckpointToGo;

	int lapDiff = heighestLap - racer->FindComponentByClass<UPlayerStats_AC>()->CurrentLap;
	float distance = 0;
	FVector racerPos = copyRacer->GetActorLocation();

	while (racerCPToGo != destination->Index)
	{
		distance += LevelCheckpoints[racerCPToGo]->getDistanceFromRacer(racerPos);
		racerPos = LevelCheckpoints[racerCPToGo]->GetActorLocation();

		if (racerCPToGo + 1 == LevelCheckpoints.Num())
			break;

		racerCPToGo++;
	}

	//UE_LOG(LogTemp, Warning, TEXT("Racer CP to go: %d"), racerCPToGo);

	distance += destination->getDistanceFromRacer(racer->GetActorLocation());

	return distance;
}
