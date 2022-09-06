// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotionPickup.h"

#include "SAttributeComponent.h"


ASHealthPotionPickup::ASHealthPotionPickup()
{
	HealthRestore = 50.0f;
}

void ASHealthPotionPickup::Interact_Implementation(APawn* InstigatorPawn)
{
	USAttributeComponent* AttributeComp = InstigatorPawn->FindComponentByClass<USAttributeComponent>();
	if(AttributeComp)
	{
		if(!AttributeComp->ApplyHealthChange(HealthRestore))
		{
			return;
		}
	}
	Super::Interact_Implementation(InstigatorPawn);
}
