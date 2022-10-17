// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

#include "SGameModeBase.h"
#include "Net/UnrealNetwork.h"

static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.DamageMultiplier"), 1.0f, TEXT("Global Damage Modifier for Attribute Component."), ECVF_Cheat);

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	MaxHealth = 100.0f;
	Health = MaxHealth;

	MaxRage = 30.0f;
	Rage = 0.0f;

	SetIsReplicatedByDefault(true);
}

void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

float USAttributeComponent::GetHealth()
{
	return Health;
}

float USAttributeComponent::GetMaxHealth()
{
	return MaxHealth;
}

float USAttributeComponent::GetRage()
{
	return Rage;
}

float USAttributeComponent::GetMaxRage()
{
	return MaxRage;
}

bool USAttributeComponent::ApplyRageChange(AActor* InstigatorActor, float Delta)
{
	const float OldRage = Rage;


	Rage = FMath::Clamp(Rage + Delta, 0.0f, MaxRage);
	UE_LOG(LogTemp, Log, TEXT("Adding Rage Delta %f, New Rage %f, OldRage %f"), Delta, Rage, OldRage);
	const float ActualDelta = Rage - OldRage;
	// OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);


	UE_LOG(LogTemp, Log, TEXT("Checking Rage Delta %f, ActualDelta %f"), Delta, ActualDelta);

	if(ActualDelta != 0.0f)
	{
		UE_LOG(LogTemp, Log, TEXT("Called Rage Multicast!"));
		MulticastRageChanged(InstigatorActor, Rage, ActualDelta);
	}

	return ActualDelta != 0;
}


bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if(!GetOwner()->CanBeDamaged() && Delta < 0.0f)
	{
		return false;
	}
	if(Delta < 0.0f)
	{
		const float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();

		Delta *= DamageMultiplier;
	}
	const float OldHealth = Health;
	const float NewHealth = FMath::Clamp(Health + Delta, 0.0f, MaxHealth);

	const float ActualDelta = NewHealth - OldHealth;
	// OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);

	// Is Server?
	if(GetOwner()->HasAuthority())
	{
		Health = NewHealth;

		if(ActualDelta != 0.0f)
		{
			MulticastHealthChanged(InstigatorActor, Health, ActualDelta);
		}

		// Died
		if(ActualDelta < 0.0f && Health == 0.0f)
		{
			ASGameModeBase* GM = GetWorld()->GetAuthGameMode<ASGameModeBase>();

			if(GM)
			{
				GM->OnActorKilled(GetOwner(), InstigatorActor);
			}
		}
	}

	return ActualDelta != 0;
}

bool USAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -MaxHealth);
}

USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(StaticClass()));
	}

	return nullptr;
}

bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
	USAttributeComponent* AttributeComp = GetAttributes(Actor);
	if(AttributeComp)
	{
		return AttributeComp->IsAlive();
	}

	return false;
}

void USAttributeComponent::MulticastHealthChanged_Implementation(AActor* InstigatorActor, float NewHealth, float Delta)
{
	OnHealthChanged.Broadcast(InstigatorActor, this, NewHealth, Delta);
}

void USAttributeComponent::MulticastRageChanged_Implementation(AActor* InstigatorActor, float NewRage, float Delta)
{
	OnRageChanged.Broadcast(InstigatorActor, this, NewRage, Delta);
}

void USAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USAttributeComponent, Health);
	DOREPLIFETIME(USAttributeComponent, MaxHealth);
	DOREPLIFETIME(USAttributeComponent, Rage);
	DOREPLIFETIME(USAttributeComponent, MaxRage);
	// DOREPLIFETIME_CONDITION(USAttributeComponent, MaxHealth, COND_InitialOnly);
}