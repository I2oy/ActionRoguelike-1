// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemPickup.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ASItemPickup::ASItemPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Pickup");
	SphereComp->SetIsReplicated(true);
	RootComponent = SphereComp;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ItemMesh->SetIsReplicated(true);
	ItemMesh->SetupAttachment(RootComponent);

	RespawnTime = 10.0f;

	SetReplicates(true);
}

void ASItemPickup::Interact_Implementation(APawn* InstigatorPawn)
{
	HideAndCooldownPowerUp();
}

void ASItemPickup::Respawn()
{
	SetPickupState(true);
}

void ASItemPickup::HideAndCooldownPowerUp()
{
	SetPickupState(false);
	GetWorldTimerManager().SetTimer(TimerHandle_Respawn, this, &ASItemPickup::Respawn, RespawnTime);
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

void ASItemPickup::OnRep_IsActive()
{
	SetActorEnableCollision(bIsActive);
	// set visibility on root and all children
	RootComponent->SetVisibility(bIsActive, true);
}

void ASItemPickup::SetPickupState(bool bNewIsActive)
{
	bIsActive = bNewIsActive;
	OnRep_IsActive();
}

void ASItemPickup::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASItemPickup, bIsActive);
}
