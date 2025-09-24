// Fill out your copyright notice in the Description page of Project Settings.


#include "CPCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"

// Sets default values
ACPCharacterBase::ACPCharacterBase()
{
	// Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	// Movement
	GetCharacterMovement()->GravityScale = 1.5f;
	GetCharacterMovement()->MaxAcceleration = 1000.0f;
	GetCharacterMovement()->BrakingFrictionFactor = 1.0f;
	GetCharacterMovement()->PerchRadiusThreshold = 20.0f;
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 0.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.0f;
	GetCharacterMovement()->JumpZVelocity = 420.0f;
	GetCharacterMovement()->AirControl = 0.05f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);

	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterSkeletalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Assassin/Mesh/SKM_Assassin_Skin1.SKM_Assassin_Skin1'"));
	if (CharacterSkeletalMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterSkeletalMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/carusinaProject/Animation/ABP_CPCharacterPlayer.ABP_CPCharacterPlayer_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	// Animation
	bCanDodge = true;
	DodgeCooldownDuration = 5.0f;
}

void ACPCharacterBase::ProcessBasicAttack()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(BasicAttackMontage);
}

void ACPCharacterBase::ProcessDodge()
{
	if (!bCanDodge)
	{
		UE_LOG(LogTemp, Log, TEXT("Dodge is CoolDown."));
		return;
	}

	bCanDodge = false;
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(DodgeMontage);
	GetWorld()->GetTimerManager().SetTimer(DodgeCooldownTimer, this, &ACPCharacterBase::ClearDodgeCooldown, DodgeCooldownDuration, false);
}

void ACPCharacterBase::ClearDodgeCooldown()
{
	bCanDodge = true;
}
