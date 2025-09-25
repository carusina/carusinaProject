// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterStat/CPCharacterStat.h"
#include "CPGameSingleton.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCPGameSingleton, Error, All);

/**
 * 
 */
UCLASS()
class CARUSINAPROJECT_API UCPGameSingleton : public UObject
{
	GENERATED_BODY()

public:
	UCPGameSingleton();

	static UCPGameSingleton& Get();

	FORCEINLINE FCPCharacterStat GetCharacterStat(int32 Level) const { return CharacterStatTable.IsValidIndex(Level - 1) ? CharacterStatTable[Level - 1] : FCPCharacterStat(); }
	FORCEINLINE int32 GetCharacterMaxLevel() const { return CharacterMaxLevel; }

private:
	UPROPERTY()
	int32 CharacterMaxLevel;
	
	TArray<FCPCharacterStat> CharacterStatTable;
};
