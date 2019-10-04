// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_A.h"
#include "PlayerStats_AC.h"
#include "OffensiveWeapon_Item_A.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class AttackType : uint8
{
	Linear,
	Radial,
	Buff,
	None
};

UCLASS()
class RPG_RACERS_API AOffensiveWeapon_Item_A : public AItem_A
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float BaseDamage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		AttackType OffWeaponType = AttackType::None;

	UFUNCTION(BlueprintImplementableEvent)
		void ActivateWeapon(UPlayerStats_AC* PlayerStats);

	UFUNCTION(BlueprintCallable)
		float CalculateDamage(UPlayerStats_AC* PlayerStats);
};
