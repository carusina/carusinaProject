// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPCharacterBase.generated.h"

UCLASS()
class CARUSINAPROJECT_API ACPCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPCharacterBase();
	
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
};
