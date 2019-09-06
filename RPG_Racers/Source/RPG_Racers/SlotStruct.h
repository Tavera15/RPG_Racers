// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "Item_A.h"
#include "ItemStruct.h"
#include "SlotStruct.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType)
struct FSlotStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AItem_A* Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FColor Color;

	FSlotStruct()
	{
		auto EmptyItemStruct = FItemStruct::FItemStruct();
		Item = AItem_A::GetEmptyItem();
		Item->ItemStructure = EmptyItemStruct;
		Color = FColor::White;
	}

	bool operator==(const FSlotStruct& OtherItem) const
	{
		return Item->ItemStructure.ID == OtherItem.Item->ItemStructure.ID;		// Returns true if OtherItem is empty
	}
};
