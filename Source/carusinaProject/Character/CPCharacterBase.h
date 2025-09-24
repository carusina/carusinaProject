// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/CPAnimationAttackyInterface.h"
#include "Interface/CPCharacterWidgetInterface.h"
#include "CPCharacterBase.generated.h"

UCLASS()
class CARUSINAPROJECT_API ACPCharacterBase : public ACharacter, public ICPAnimationAttackyInterface, public ICPCharacterWidgetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPCharacterBase();

	virtual void PostInitializeComponents() override;
	
	// Basic Attack Action
	void ProcessBasicAttack();
	void ProcessDodge();

protected:
	// Basic Attack Action
	void ClearDodgeCooldown();
	void BasicActionBegin();
	void BasicActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);
	void SetComboCheckTimer();
	void ComboCheck();
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Dead Section
	virtual void SetDead();
	void PlayDeadAnimation();
	
	// AnimNotify Section
	virtual void AttackHitCheck() override;

	// UI Widget Section
	virtual void SetupCharacterWidget(class UCPUserWidget* UserWidget) override;
	
protected:
	// Basic Attack Action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> BasicAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|Attack")
	TObjectPtr<class UABActionComboData> ActionComboData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> DodgeMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation|Dodge")
	uint8 bCanDodge : 1 = true;

	float DodgeCooldownDuration = 5.0f;
	int32 CurrentCombo = 0;
	uint8 HasNextComboCommand : 1 = false;
	
	FTimerHandle DodgeCooldownTimer;
	FTimerHandle ComboTimerHandle;

	// Dead Section
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|Dead")
	TObjectPtr<class UAnimMontage> DeadMontage;

	float DeadEventDelay = 5.0f;

	// Stat Section
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCPCharacterStatComponent> Stat;

	// UI Widget Section
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget|Health", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCPWidgetComponent> HealthBar;
};
