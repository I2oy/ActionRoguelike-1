// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SItemPickup.h"
#include "SActionPickup.generated.h"

class USAction;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASActionPickup : public ASItemPickup
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Powerup")
	TSubclassOf<USAction> ActionToGrant;

public:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};
