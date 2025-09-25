// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Dectect.generated.h"

/**
 * 
 */
UCLASS()
class CARUSINAPROJECT_API UBTService_Dectect : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_Dectect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
