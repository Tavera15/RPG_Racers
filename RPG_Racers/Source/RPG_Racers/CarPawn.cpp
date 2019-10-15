// Fill out your copyright notice in the Description page of Project Settings.

#include "CarPawn.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"

// Sets default values
ACarPawn::ACarPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerStats = CreateDefaultSubobject<UPlayerStats_AC>(FName("PlayerStats"));
	CarMovementComp = CreateDefaultSubobject<UCarMovementComponent>(FName("CarMovementComp"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(FName("InventoryComponent"));
}

// Called when the game starts or when spawned
void ACarPawn::BeginPlay()
{
	Super::BeginPlay();

	if(!isNPC)
		InventoryComponent->AddToWindow();
	
	TArray<AActor*> AllStores;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStore_A::StaticClass(), AllStores);

	if(AllStores.Num() > 0)
		TheStore = Cast<AStore_A>(AllStores[0]);

	TArray<AActor*> AllCheckpoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACheckpoint_A::StaticClass(), AllCheckpoints);

	for (int i = 0; i < AllCheckpoints.Num(); i++)
		PlayerStats->checkpoints.Add(Cast<ACheckpoint_A>(AllCheckpoints[i]));

}

// Called every frame
void ACarPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

// Called to bind functionality to input
void ACarPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACarPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACarPawn::MoveRight);
	PlayerInputComponent->BindAction("OpenStore", IE_Pressed, this, &ACarPawn::OpenStore);
	PlayerInputComponent->BindAction("UseWeapon", IE_Pressed, this, &ACarPawn::UseWeapon);
}

void ACarPawn::OpenStore()
{
	if (isNPC || !TheStore) { return; }

	auto StoreInvComp = TheStore->FindComponentByClass<UInventoryComponent>();
	auto MyPlayerController = Cast<APlayerController>(GetController());

	if (!MyPlayerController || !StoreInvComp) { return; }

	if (StoreInvComp->InventoryWindow && StoreInvComp->InventoryWindow->IsInViewport())
	{
		StoreInvComp->InventoryWindow->RemoveFromViewport();
		MyPlayerController->bShowMouseCursor = false;
		MyPlayerController->SetInputMode(FInputModeGameOnly::FInputModeGameOnly());
		return;
	}

	StoreInvComp->AddToWindow();
	MyPlayerController->bShowMouseCursor = true;
	MyPlayerController->SetInputMode(FInputModeGameAndUI::FInputModeGameAndUI());
}

void ACarPawn::UseWeapon()
{
	if (!OffensiveWeapon) { return; }

	OffensiveWeapon->ActivateWeapon(PlayerStats);
}

void ACarPawn::MoveForward(float value)
{
	if (!CarMovementComp) { return; }

	CarMovementComp->SetThrottle(value);
}

void ACarPawn::MoveRight(float value)
{
	if (!CarMovementComp) { return; }

	CarMovementComp->SetSteeringThrow(value);
}

