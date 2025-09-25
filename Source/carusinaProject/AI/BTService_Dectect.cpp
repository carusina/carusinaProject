// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_Dectect.h"
#include "AIController.h"
#include "Interface/CPNonPlayerInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Physics/CPCollision.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"

UBTService_Dectect::UBTService_Dectect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Dectect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControlledPawn == nullptr)
	{
		return;
	}

	FVector Center = ControlledPawn->GetActorLocation();
	UWorld* World = ControlledPawn->GetWorld();
	if (World == nullptr)
	{
		return;
	}

	ICPNonPlayerInterface* AIPawn = Cast<ICPNonPlayerInterface>(ControlledPawn);
	if (AIPawn == nullptr)
	{
		return;
	}

	float DetectRadius = AIPawn->GetAIDecteRange();

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(SCENE_QUERY_STAT(Detect), false, ControlledPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		CCHANNEL_CPACTION,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam);

	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			APawn* Pawn = Cast<APawn>(OverlapResult.GetActor());
			if (Pawn && Pawn->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), Pawn);
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);

				DrawDebugPoint(World, Pawn->GetActorLocation(), 10.0f, FColor::Green, false, 0.2f);
				DrawDebugLine(World, ControlledPawn->GetActorLocation(), Pawn->GetActorLocation(), FColor::Green, false, 0.27f);
				return;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}
