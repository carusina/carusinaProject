// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPCharacterStat.h"
#include "Components/ActorComponent.h"
#include "CPCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHealthZeroDelegate);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedDelegate, float /* Current Hp */, float /* MaxHealth */);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CARUSINAPROJECT_API UCPCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPCharacterStatComponent();
	
protected:
	virtual void InitializeComponent() override;
	
public:
	FORCEINLINE const FCPCharacterStat& GetBaseStat() const { return BaseStat; }
	FORCEINLINE void SetBaseStat(const FCPCharacterStat& NewBaseStat) { BaseStat = NewBaseStat; }

	FORCEINLINE const FCPCharacterStat& GetBonusStat() const { return BonusStat; }
	FORCEINLINE void AddBonusStat(const FCPCharacterStat& NewBonusStat) { BonusStat = BonusStat + NewBonusStat; }

	FORCEINLINE FCPCharacterStat GetTotalStat() const { return BaseStat + BonusStat; }

	FORCEINLINE int32 GetCurrentLevel() const { return CurrentLevel; }
	void SetLevel(int32 NewLevel);
	
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }
	void SetCurrentHealth(float NewHealth);
	void HealHealth(float HealAmount);
	
	float ApplyDamage(float DamageAmount);

	FORCEINLINE float GetAttackRadius() const { return AttackRadius; }
	
public:
	FOnHealthZeroDelegate OnHealthZero;
	FOnHealthChangedDelegate OnHealthChanged;
	
protected:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	FCPCharacterStat BaseStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	FCPCharacterStat BonusStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	int32 CurrentLevel;
	
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat|Health")
	float CurrentHealth;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat|Attack")
	float AttackRadius;
};
