// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Components/ActorComponent.h"
#include "SimpleWheeledVehicleMovementComponent.h"
#include "CarMovementComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_RACERS_API UCarMovementComponent : public USimpleWheeledVehicleMovementComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCarMovementComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*
	UPROPERTY(EditAnywhere)
		float Mass = 1000;


	UPROPERTY(EditAnywhere)
		float DragCoefficient = 16;
	*/

	UPROPERTY(EditAnywhere)
		float MaxDrivingForce = 10000;

	UPROPERTY(EditAnywhere)
		float MinTurnRadius = 10;

	UPROPERTY(EditAnywhere)
		float MaxDegreesPerSecond = 90;

	UPROPERTY(EditAnywhere)
		float RollingCoefficient = 0.005;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool canMove = false;

	void SetThrottle(float Val) { Throttle = Val; };
	void SetSteeringThrow(float Val) { SteeringThrow = Val; };

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	/*
	FVector Velocity;
	*/
	float SteeringThrow;
	float Throttle;

	void SimulateMove(float);
	FVector GetAirResistance();
	FVector GetRollingResistance();
	void ApplyRotation(float);
	void UpdateLocationFromVelocity(float);

};
 