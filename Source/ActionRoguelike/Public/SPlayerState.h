// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCreditChanged, AActor*, InstigatorActor, APlayerState*, OwningComp, float, NewCredit, float, Delta);

class USSaveGame;

UCLASS()
class ACTIONROGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Credits;

public:

	UFUNCTION(BlueprintCallable)
	int32 AddCredits(AActor* InstigatorActor, int32 Amount);

	UFUNCTION(BlueprintCallable)
	bool SpendCredits(AActor* InstigatorActor, int32 Amount);

	UPROPERTY(BlueprintAssignable)
	FOnCreditChanged OnCreditChanged;

	UFUNCTION(BlueprintNativeEvent)
	void SavePlayerState(USSaveGame* SaveObject);

	UFUNCTION(BlueprintNativeEvent)
	void LoadPlayerState(USSaveGame* SaveObject);

};
