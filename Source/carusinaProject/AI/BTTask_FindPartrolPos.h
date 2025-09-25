// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindPartrolPos.generated.h"

/**
 * 
 */
UCLASS()
class CARUSINAPROJECT_API UBTTask_FindPartrolPos : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FindPartrolPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
