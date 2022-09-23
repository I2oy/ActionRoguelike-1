// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoinPickup.h"

ASCoinPickup::ASCoinPickup()
{
	CreditAmount = 1;
}

void ASCoinPickup::Interact_Implementation(APawn* InstigatorPawn)
{
	UE_LOG(LogTemp, Log, TEXT("Called Coin Interact!"));
	Super::Interact_Implementation(InstigatorPawn);
}