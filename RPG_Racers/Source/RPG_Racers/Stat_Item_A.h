// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_A.h"
#include "Stat_Item_A.generated.h"

/**
 * 
 */
UCLASS()
class RPG_RACERS_API AStat_Item_A : public AItem_A
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float AttackPower = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float DefensiveProtections = 0.0f;

	static AStat_Item_A* GetEmptyStatItem();

private:
	void TestChild();
};
 