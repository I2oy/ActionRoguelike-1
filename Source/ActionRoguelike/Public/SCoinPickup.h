// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SItemPickup.h"
#include "SCoinPickup.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASCoinPickup : public ASItemPickup
{
	GENERATED_BODY()
public:

	ASCoinPickup();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Pickup Effects");
	int32 CreditAmount;

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};
