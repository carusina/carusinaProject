// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FindPartrolPos.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/CPNonPlayerInterface.h"

UBTTask_FindPartrolPos::UBTTask_FindPartrolPos()
{
}

EBTNodeResult::Type UBTTask_FindPartrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControlledPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem((ControlledPawn->GetWorld()));
	if (NavSystem == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	ICPNonPlayerInterface* AIPawn = Cast<ICPNonPlayerInterface>(ControlledPawn);
	if (AIPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("HomePos"));
	FNavLocation NextPatrolPos;
	float PatrolRadius = AIPawn->GetAIPatrolRadius();
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, PatrolRadius, NextPatrolPos))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolPos"), NextPatrolPos);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
