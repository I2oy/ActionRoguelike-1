// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SItemPickup.h"
#include "SHealthPotionPickup.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASHealthPotionPickup : public ASItemPickup
{
	GENERATED_BODY()

public:

	ASHealthPotionPickup();
	
	UPROPERTY(EditDefaultsOnly, Category="Pickup Effects");
	float HealthRestore;
	
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};