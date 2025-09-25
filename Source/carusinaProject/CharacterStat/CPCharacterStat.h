#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CPCharacterStat.generated.h"

USTRUCT(BlueprintType)
struct FCPCharacterStat : public FTableRowBase
{
	GENERATED_BODY()

public:
	FCPCharacterStat() : MaxHealth(0.0f), MaxStamina(0.0f),
						 AttackDamage(0.0f), AttackRange(0.0f), AttackSpeed(0.0f),
					     MovementSpeed(0.0f), RequiredExperience(0.0f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float RequiredExperience;

	FCPCharacterStat operator+(const FCPCharacterStat& Other) const
	{
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		FCPCharacterStat Result;
		float* ResultPtr = reinterpret_cast<float* >(&Result);
		int32 StatNum = sizeof(FCPCharacterStat) / sizeof(float);
		for (int32 i = 0; i < StatNum; i++)
		{
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];
		}

		return Result;
	}
};