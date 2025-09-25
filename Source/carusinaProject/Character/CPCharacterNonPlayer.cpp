// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CPCharacterNonPlayer.h"
#include "CPCharacterPlayer.h"
#include "AI/CPAIController.h"
#include "CharacterStat/CPCharacterStatComponent.h"

ACPCharacterNonPlayer::ACPCharacterNonPlayer()
{
	AIControllerClass = ACPAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
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

float ACPCharacterNonPlayer::GetAIPatrolRadius()
{
	return 800.0f;
}

float ACPCharacterNonPlayer::GetAIDecteRange()
{
	return 400.0f;
}

float ACPCharacterNonPlayer::GetAIAttackRange()
{
	return Stat->GetTotalStat().AttackRange + Stat->GetAttackRadius() * 2.0f;
}

float ACPCharacterNonPlayer::GetAITurnSpeed()
{
	return 2.0f;
}

void ACPCharacterNonPlayer::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void ACPCharacterNonPlayer::AttackByAI()
{
	ProcessBasicAttack();
}

void ACPCharacterNonPlayer::NotifyBasicActionEnd()
{
	Super::NotifyBasicActionEnd();
	OnAttackFinished.ExecuteIfBound();
}
