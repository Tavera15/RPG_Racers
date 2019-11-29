// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerStats_AC.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Controller.h"


// Sets default values for this component's properties
UPlayerStats_AC::UPlayerStats_AC()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UPlayerStats_AC::BeginPlay()
{
	Super::BeginPlay();
	// ...


	TArray<AActor*> allPlayerCheckpoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCheckpoints_A::StaticClass(), allPlayerCheckpoints);
	
	if(allPlayerCheckpoints.Num() > 0)
		LevelCheckpoints = Cast<APlayerCheckpoints_A>(allPlayerCheckpoints[0]);
}


// Called every frame
void UPlayerStats_AC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerStats_AC::ReceiveDamage(float DamageTaken)
{
	DamageTaken -= DefensiveProtections;
	HP -= DamageTaken;

	if (HP <= 0)
	{
		PlayerDead();
		UE_LOG(LogTemp, Warning, TEXT("Killed"));
	}
}

int UPlayerStats_AC::UpdateCheckpoint(int checkpointOn)
{
	if (checkpointOn != CheckpointToGo)
	{
		return CheckpointToGo;
	}

	if (CheckpointToGo + 1 == LevelCheckpoints->LevelCheckpoints.Num())
	{
		CheckpointToGo = 0;
		CurrentLap++;
	}
	else
	{
		CheckpointToGo++;
	}

	TemporaryRespawn = LevelCheckpoints->LevelCheckpoints[CheckpointToGo];

	return CheckpointToGo;
}

void UPlayerStats_AC::PlayerDead()
{
	auto currentPosition = GetOwner()->GetActorLocation();

	//auto control = GetOwner()->GetInstigatorController();
	
	//if (!control) { return; }

	//GetOwner()->SetActorLocation(TemporaryRespawn->GetActorLocation());

	// ToDo Will spawn at the last checkpoint when car is dead
	HP = 100;

}

