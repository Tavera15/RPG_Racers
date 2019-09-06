// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "ItemStruct.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ItemType : uint8
{
	Attack,
	Defense,
	OffensiveWeapon,
	None
};

USTRUCT(BlueprintType)
struct FItemStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		int ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FString ItemDesc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		ItemType TypeOfItem;


	FItemStruct()
	{
		ID = 0;
		ItemName = "";
		ItemDesc = "";
		Thumbnail = NULL;
		TypeOfItem = ItemType::None;
	}

};
