// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NiagaraFunctionLibrary.h"
#include "CPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CARUSINAPROJECT_API ACPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPPlayerController();

protected:
	virtual void BeginPlay() override;

	// Player Input Section
	virtual void SetupInputComponent() override;

private:
	// Player Input Section
	void GetLocationUnderCursor();
	void MoveToLocation();
	void BasicAttack();
	void Dodge();
	
protected:
	// Player Input Section
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> SetDestinationAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> BasicAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> DodgeAction;

private:
	// Controlled Character
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Controlled, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ACPCharacterPlayer> ControlledCharacter;
	
	// Player Input Section
	FVector GoalLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraSystem> FXCursor;
};
