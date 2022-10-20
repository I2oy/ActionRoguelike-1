// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotionPickup.h"

#include "SAttributeComponent.h"
#include "SPlayerState.h"


ASHealthPotionPickup::ASHealthPotionPickup()
{
	HealthRestore = 50.0f;
}

void ASHealthPotionPickup::Interact_Implementation(APawn* InstigatorPawn)
{
	ASPlayerState* PlayerState = Cast<ASPlayerState>(InstigatorPawn->Controller->PlayerState);
	if(PlayerState)
	{
		USAttributeComponent* AttributeComp = InstigatorPawn->FindComponentByClass<USAttributeComponent>();
		if(AttributeComp)
		{
			if(!PlayerState->RemoveCredits(-5))
			{
				return;
			}
			if(!AttributeComp->ApplyHealthChange(this, HealthRestore))
			{
				return;
			}
		}
	}
	Super::Interact_Implementation(InstigatorPawn);
}
