// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_Heal.h"
#include "AIController.h"
#include "SAttributeComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type USBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* AIController = OwnerComp.GetAIOwner();

	if(ensure(AIController))
	{
		ACharacter* AIPawn = Cast<ACharacter>(AIController->GetPawn());
		if(AIPawn == nullptr)
		{
				return EBTNodeResult::Failed;
		}

		if(USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(AIPawn))
		{
			if(AttributeComp->ApplyHealthChange(AIPawn, AttributeComp->GetMaxHealth()))
			{
				if(HealEffectClass)
				{
					UGameplayStatics::SpawnEmitterAttached(HealEffectClass, AIPawn->GetMesh(), "Chest");
				}
				return EBTNodeResult::Succeeded;
			}
		}		

	}


	return EBTNodeResult::Failed;
}
