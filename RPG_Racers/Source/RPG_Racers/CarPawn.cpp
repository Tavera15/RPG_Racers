// Fill out your copyright notice in the Description page of Project Settings.

#include "CarPawn.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
ACarPawn::ACarPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(FName("InventoryComponent"));

}

// Called when the game starts or when spawned
void ACarPawn::BeginPlay()
{
	Super::BeginPlay();
	InventoryComponent->AddToWindow();
	
	TArray<AActor*> AllStores;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStore_A::StaticClass(), AllStores);

	if(AllStores.Num() > 0)
		TheStore = Cast<AStore_A>(AllStores[0]);

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
	//PlayerInputComponent->BindAxis("MoveForward", this, &ACarPawn::MoveForward);
	//PlayerInputComponent->BindAxis("MoveRight", this, &ACarPawn::MoveRight);
	PlayerInputComponent->BindAction("OpenStore", IE_Pressed, this, &ACarPawn::OpenStore);
}

void ACarPawn::OpenStore()
{
	if (!TheStore) { return; }

	auto StoreInvComp = TheStore->FindComponentByClass<UInventoryComponent>();
	auto MyPlayerController = GetWorld()->GetFirstPlayerController();

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
