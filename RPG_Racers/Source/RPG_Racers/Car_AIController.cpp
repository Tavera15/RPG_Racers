// Fill out your copyright notice in the Description page of Project Settings.

#include "Car_AIController.h"
#include "CarPawn.h"
#include "CarMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void ACar_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto OwnerCar = GetPawn();
	auto Destination = Cast<ACarPawn>(OwnerCar)->TheStore;

	if (!OwnerCar || !Destination) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Bad Car"));
		return; 
	}
	
	//Cast<ACarPawn>(OwnerCar)->DriveToDestination();
	//MoveToActor(Destination, AcceptableRadius);

	/*
	if (OwnerCar->IsOverlappingActor(Destination))
	{
		Cast<ACarPawn>(OwnerCar)->FindComponentByClass<UCarMovementComponent>()->Velocity = FVector::ZeroVector;
	}
	else
	{
		//Cast<ACarPawn>(OwnerCar)->MoveRight(AimAtAngle);
		//OwnerCar->DriveToDestination();
		//GetPawn()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(OwnerCar->GetActorLocation(), Destination->GetActorLocation()));
		
		Cast<ACarPawn>(OwnerCar)->DriveToDestination();
	}
	*/

}