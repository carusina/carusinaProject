// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData/CPGameSingleton.h"

DEFINE_LOG_CATEGORY(LogCPGameSingleton);

UCPGameSingleton::UCPGameSingleton()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterStatDataTableRef(TEXT("/Script/Engine.DataTable'/Game/carusinaProject/CharacterStat/DT_CPCharacterStat.DT_CPCharacterStat'"));
	if (CharacterStatDataTableRef.Object)
	{
		const UDataTable* CharacterStatDataTable = CharacterStatDataTableRef.Object;
		check(CharacterStatDataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray;
		CharacterStatDataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, CharacterStatTable,
			[](uint8* Value)
			{
				return *reinterpret_cast<FCPCharacterStat*>(Value);
			});
	}

	CharacterMaxLevel = CharacterStatTable.Num();
	ensure(CharacterMaxLevel > 0);
}

UCPGameSingleton& UCPGameSingleton::Get()
{
	UCPGameSingleton* Singleton = CastChecked<UCPGameSingleton>(GEngine->GameSingleton);
	if (Singleton)
	{
		return *Singleton;
	}

	UE_LOG(LogCPGameSingleton, Error, TEXT("Invalid Game Singleton"));
	return *NewObject<UCPGameSingleton>();
}
