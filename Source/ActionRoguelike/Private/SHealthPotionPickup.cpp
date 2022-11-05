// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotionPickup.h"

#include "SAttributeComponent.h"
#include "SPlayerState.h"

#define LOCTEXT_NAMESPACE "InteractableActors"

ASHealthPotionPickup::ASHealthPotionPickup()
{
	HealthRestore = 50.0f;
	CreditCost = 5;
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

FText ASHealthPotionPickup::GetInteractText_Implementation(APawn* InstigatorPawn)
{
	USAttributeComponent* AttributeComp = InstigatorPawn->FindComponentByClass<USAttributeComponent>();
	if(AttributeComp && AttributeComp->IsFullHealth())
	{
		return LOCTEXT("HealthPotion_FullHealthWarning", "Already at full health.");
	}

	return FText::Format(LOCTEXT("HealthPotion_InteractMessage", "Cost {0} Credits. restores health to maximum."), CreditCost);

}

#undef LOCTEXT_NAMESPACE