// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemStruct.h"
#include "Item_A.generated.h"

UCLASS()
class RPG_RACERS_API AItem_A : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem_A();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FItemStruct ItemStructure;

	static AItem_A* GetEmptyItem();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

};
