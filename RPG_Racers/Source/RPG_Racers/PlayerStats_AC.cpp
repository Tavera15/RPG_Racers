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

	isImmune = false;

	TArray<AActor*> allPlayerCheckpoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCheckpoints_A::StaticClass(), allPlayerCheckpoints);
	
	if(allPlayerCheckpoints.Num() > 0)
		LevelCheckpoints = Cast<APlayerCheckpoints_A>(allPlayerCheckpoints[0]);

	UE_LOG(LogTemp, Warning, TEXT("test"));
}


// Called every frame
void UPlayerStats_AC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UPlayerStats_AC::ReceiveDamage(float DamageTaken)
{
	bool isRacerDead = false;

	if (isImmune) { return isRacerDead; }

	DamageTaken -= DefensiveProtections;

	if (DamageTaken < 0)
		DamageTaken = 5;

	HP -= DamageTaken;

	if (HP <= 0)
	{
		PlayerDead();
		isRacerDead = true;
	}

	return isRacerDead;
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
	isDead = true;
	canMove = false;
}


void UPlayerStats_AC::Respawn()
{
	int indexToSpawn = (CheckpointToGo - 2 < 0 ? LevelCheckpoints->LevelCheckpoints.Num() - 1 : CheckpointToGo - 2);
	GetOwner()->SetActorLocation(LevelCheckpoints->LevelCheckpoints[indexToSpawn]->GetActorLocation());
	HP = 100;
	isDead = false;
	canMove = true;
}
