// Fill out your copyright notice in the Description page of Project Settings.

#include "Stat_Item_A.h"

void AStat_Item_A::TestChild()
{
	UE_LOG(LogTemp, Warning, TEXT("Test Child"));
}

AStat_Item_A* AStat_Item_A::GetEmptyStatItem()
{
	auto EmptyStatItem = NewObject<AStat_Item_A>();
	EmptyStatItem->ItemStructure = FItemStruct::FItemStruct();
	EmptyStatItem->AttackPower = 0.0f;
	EmptyStatItem->DefensiveProtections = 0.0f;
	EmptyStatItem->DrivingSpeed = 1.0f;

	return EmptyStatItem;
}