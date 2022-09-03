// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemPickup.h"

// Sets default values
ASItemPickup::ASItemPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = ItemMesh;
}

void ASItemPickup::Interact_Implementation(APawn* InstigatorPawn)
{
	GetWorldTimerManager().SetTimer(TimerHandle_Respawn, this, &ASItemPickup::Respawn, 3.0);
	this->SetActorEnableCollision(false);
	this->SetActorHiddenInGame(true);
	
}

void ASItemPickup::Respawn()
{
	this->SetActorEnableCollision(true);
	this->SetActorHiddenInGame(false);
}

// Called when the game starts or when spawned
void ASItemPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASItemPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

