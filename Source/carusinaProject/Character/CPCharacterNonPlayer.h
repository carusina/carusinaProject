// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CPCharacterBase.h"
#include "Interface/CPNonPlayerInterface.h"
#include "CPCharacterNonPlayer.generated.h"

/**
 * 
 */
UCLASS()
class CARUSINAPROJECT_API ACPCharacterNonPlayer : public ACPCharacterBase, public ICPNonPlayerInterface
{
	GENERATED_BODY()

public:
	ACPCharacterNonPlayer();

protected:
	virtual void SetDead() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// AI Section
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDecteRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;
	virtual void AttackByAI() override;
	virtual void NotifyBasicActionEnd() override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience")
	float ExperienceReward;

	// AI Section
	FAICharacterAttackFinished OnAttackFinished;
};
