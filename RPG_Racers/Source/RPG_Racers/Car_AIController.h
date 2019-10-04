// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CarPawn.h"
#include "Car_AIController.generated.h"

/**
 * 
 */
UCLASS()
class RPG_RACERS_API ACar_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float) override;
	
	UPROPERTY(EditAnywhere)
		float AcceptableRadius = 1000.0f;
	
};
