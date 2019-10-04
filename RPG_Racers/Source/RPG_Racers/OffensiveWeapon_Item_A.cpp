// Fill out your copyright notice in the Description page of Project Settings.

#include "OffensiveWeapon_Item_A.h"

float AOffensiveWeapon_Item_A::CalculateDamage(UPlayerStats_AC * PlayerStats)
{	
	return (PlayerStats->AttackPower + BaseDamage);
}
