// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

int32 ASPlayerState::AddCredits(AActor* InstigatorActor, int32 Amount)
{
	Credits += Amount;
	OnCreditChanged.Broadcast(InstigatorActor, this, Credits, Amount);
	return Credits;
}

bool ASPlayerState::SpendCredits(AActor* InstigatorActor, int32 Amount)
{
	if (Amount > Credits)
	{
		return false;
	}
	Credits -= Amount;
	OnCreditChanged.Broadcast(InstigatorActor, this, Credits, -Amount);
	return true;
}
