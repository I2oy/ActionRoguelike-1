// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SAICharacter.generated.h"

class USWorldUserWidget;
class USAttributeComponent;
class UPawnSensingComponent;
class USActionComponent;
UCLASS()
class ACTIONROGUELIKE_API ASAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASAICharacter();

	virtual void PostInitializeComponents() override;
	
protected:

	FName TargetActorKey;

	USWorldUserWidget* SpottedWidget;
	
	USWorldUserWidget* ActiveHealthBar;
	
	UPROPERTY(EditDefaultsOnly, Category="AI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	TSubclassOf<UUserWidget> SpottedWidgetClass;

	UPROPERTY(VisibleAnywhere, Category="Effects")
	FName TimeToHitParam;

	UFUNCTION()
	AActor* GetTargetActor() const;

	UFUNCTION()
	void SetTargetActor(AActor* NewTarget);

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
	void SpottedTimerElapsed();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USActionComponent* ActionComp;

public:	
	
};
