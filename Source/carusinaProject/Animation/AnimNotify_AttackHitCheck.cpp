// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AttackHitCheck.h"
#include "INterface/CPAnimationAttackyInterface.h"

void UAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
										const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		ICPAnimationAttackyInterface* AttackPawn = Cast<ICPAnimationAttackyInterface>(MeshComp->GetOwner());
		if (AttackPawn)
		{
			AttackPawn->AttackHitCheck();
		}
	}
}
