// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryComponent.h"
#include "Store_A.generated.h"

UCLASS()
class RPG_RACERS_API AStore_A : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStore_A();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UInventoryComponent* InventoryComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

};
