// Fill out your copyright notice in the Description page of Project Settings.

#include "Checkpoint_A.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "PlayerCheckpoints_A.h"

// Sets default values
ACheckpoint_A::ACheckpoint_A()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}


// Called when the game starts or when spawned
void ACheckpoint_A::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACheckpoint_A::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ACheckpoint_A::getDistanceFromRacer(FVector RacerPos)
{
	return FVector::Dist(GetActorLocation(), RacerPos);
}

