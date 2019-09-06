// Fill out your copyright notice in the Description page of Project Settings.

#include "Store_A.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AStore_A::AStore_A()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(FName("InventoryComponent"));

	StaticMesh->AttachTo(Root);
}

// Called when the game starts or when spawned
void AStore_A::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStore_A::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

