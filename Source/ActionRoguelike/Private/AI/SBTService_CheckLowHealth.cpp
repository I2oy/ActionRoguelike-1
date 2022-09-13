// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckLowHealth.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "SAttributeComponent.h"

USBTService_CheckLowHealth::USBTService_CheckLowHealth()
{
	LowHealthThreshold = 0.25f;
}

void USBTService_CheckLowHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComp =  OwnerComp.GetBlackboardComponent();
	if (ensure(BlackboardComp))
	{
		const AAIController* AIControllerComp = OwnerComp.GetAIOwner();

		if(ensure(AIControllerComp))
		{
			if(USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(AIControllerComp->GetPawn()))
			{
				const float CurrentHealthPercentage = AttributeComp->GetHealth() / AttributeComp->GetMaxHealth();
				const bool bIsLowHealth = CurrentHealthPercentage <= LowHealthThreshold;
				BlackboardComp->SetValueAsBool(LowHealthKey.SelectedKeyName, bIsLowHealth);
			}
		}
	}
	
}
