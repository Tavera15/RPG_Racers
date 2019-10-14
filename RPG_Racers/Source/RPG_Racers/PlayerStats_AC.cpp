// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerStats_AC.h"
#include "GameFramework/Actor.h"
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

void UPlayerStats_AC::PlayerDead()
{
	auto currentPosition = GetOwner()->GetActorLocation();

	auto control = GetOwner()->GetInstigatorController();
	
	if (!control) { return; }

	UE_LOG(LogTemp, Warning, TEXT("%s"), *control->GetName())

}