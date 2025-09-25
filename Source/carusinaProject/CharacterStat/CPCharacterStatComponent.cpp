// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/CPCharacterStatComponent.h"
#include "GameData/CPGameSingleton.h"

// Sets default values for this component's properties
UCPCharacterStatComponent::UCPCharacterStatComponent()
{
	CurrentLevel = 1;

	bWantsInitializeComponent = true;
}

void UCPCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevel(CurrentLevel);
	SetCurrentHealth(BaseStat.MaxHealth);
}


float UCPCharacterStatComponent::ApplyDamage(float DamageAmount)
{
	SetCurrentHealth(CurrentHealth - DamageAmount);
	if (CurrentHealth <= KINDA_SMALL_NUMBER /* 1e-4f */)
	{
		OnHealthZero.Broadcast();
	}
	
	return DamageAmount;
}

void UCPCharacterStatComponent::SetLevel(int32 NewLevel)
{
	CurrentLevel = FMath::Clamp(NewLevel, 1, UCPGameSingleton::Get().GetCharacterMaxLevel());
	BaseStat = UCPGameSingleton::Get().GetCharacterStat(CurrentLevel);
	check(BaseStat.MaxHealth > 0.0f);
}

void UCPCharacterStatComponent::SetCurrentHealth(const float NewHealth)
{
	CurrentHealth = FMath::Clamp<float>(NewHealth, 0, BaseStat.MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);
}

void UCPCharacterStatComponent::HealHealth(float HealAmount)
{
	SetCurrentHealth(CurrentHealth + HealAmount);
}
