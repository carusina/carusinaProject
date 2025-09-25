// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CPCharacterNonPlayer.h"

#include "CPCharacterPlayer.h"

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

float ACPCharacterNonPlayer::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	ACPCharacterPlayer* Player = Cast<ACPCharacterPlayer>(EventInstigator->GetPawn());
	if (Player)
	{
		Player->GainExperience(ExperienceReward);
	}
	
	return DamageAmount;
}
