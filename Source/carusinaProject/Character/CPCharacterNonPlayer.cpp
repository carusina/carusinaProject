// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CPCharacterNonPlayer.h"

ACPCharacterNonPlayer::ACPCharacterNonPlayer()
{
}

void ACPCharacterNonPlayer::SetDead()
{
	Super::SetDead();

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}), DeadEventDelay, false);
}
