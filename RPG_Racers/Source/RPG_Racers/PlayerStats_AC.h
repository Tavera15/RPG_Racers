// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OffensiveWeapon_Item_A.h"
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

	UFUNCTION(BlueprintCallable)
		void ReceiveDamage(float DamageTaken);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	bool isDead = false;

	void PlayerDead();
};
