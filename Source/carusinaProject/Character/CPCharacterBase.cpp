// Fill out your copyright notice in the Description page of Project Settings.


#include "CPCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ABActionComboData.h"
#include "CharacterStat/CPCharacterStatComponent.h"
#include "UI/CPWidgetComponent.h"
#include "Physics/CPCollision.h"
#include "Engine/DamageEvents.h"
#include "UI/CPHealthBarWidget.h"

// Sets default values
ACPCharacterBase::ACPCharacterBase()
{
	// Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_CPCAPSULE);

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
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

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

	// Stat Component
	Stat = CreateDefaultSubobject<UCPCharacterStatComponent>(TEXT("StatComponent"));
	
	// Widget Component
	HealthBar = CreateDefaultSubobject<UCPWidgetComponent>(TEXT("WidgetComponent"));
	HealthBar->SetupAttachment(GetMesh());
	HealthBar->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	static ConstructorHelpers::FClassFinder<UUserWidget> HealthBarWidgetRef(TEXT("/Game/carusinaProject/UI/WBP_Health.WBP_Health_C"));
	if (HealthBarWidgetRef.Class)
	{
		HealthBar->SetWidgetClass(HealthBarWidgetRef.Class);
		HealthBar->SetWidgetSpace(EWidgetSpace::Screen);
		HealthBar->SetDrawSize(FVector2D(150.0f, 15.0f));
		HealthBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ACPCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Stat->OnHealthZero.AddUObject(this, &ACPCharacterBase::SetDead);
}

void ACPCharacterBase::ProcessBasicAttack()
{
	if (CurrentCombo == 0)
	{
		BasicActionBegin();
		return;
	}
	if (ComboTimerHandle.IsValid())
	{
		HasNextComboCommand = true;
	}
	else
	{
		HasNextComboCommand = false;
	}
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
	AnimInstance->Montage_Play(DodgeMontage, 1.5f);
	GetWorld()->GetTimerManager().SetTimer(DodgeCooldownTimer, this, &ACPCharacterBase::ClearDodgeCooldown, DodgeCooldownDuration, false);
}

void ACPCharacterBase::ClearDodgeCooldown()
{
	DodgeCooldownTimer.Invalidate();
	bCanDodge = true;
}

void ACPCharacterBase::BasicActionBegin()
{
	// Combo Status
	CurrentCombo = 1;

	// Animation
	const float AttackSpeedRate = 1.0f;
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(BasicAttackMontage, AttackSpeedRate);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ACPCharacterBase::BasicActionEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, BasicAttackMontage);

	ComboTimerHandle.Invalidate();
	SetComboCheckTimer();
}

void ACPCharacterBase::BasicActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	ensure(CurrentCombo != 0);
	CurrentCombo = 0;
}

void ACPCharacterBase::SetComboCheckTimer()
{
	int32 ComboIndex = CurrentCombo - 1;
	ensure(ActionComboData->EffectiveFrameCount.IsValidIndex(ComboIndex));

	const float AttackSpeedRate = 1.0f;
	float ComboEffectiveTime = (ActionComboData->EffectiveFrameCount[ComboIndex] / ActionComboData->FrameRate) / AttackSpeedRate;
	if (ComboEffectiveTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &ACPCharacterBase::ComboCheck, ComboEffectiveTime, false);
	}
}

void ACPCharacterBase::ComboCheck()
{
	ComboTimerHandle.Invalidate();
	
	if (HasNextComboCommand)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ActionComboData->MaxComboCount);
		FName NextSection = *FString::Printf(TEXT("%s%d"), *ActionComboData->MontageSectionNamePrefix, CurrentCombo);
		AnimInstance->Montage_JumpToSection(NextSection, BasicAttackMontage);
		SetComboCheckTimer();
		HasNextComboCommand = false;
	}
}

float ACPCharacterBase::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	Stat->ApplyDamage(DamageAmount);
	
	return DamageAmount;
}

void ACPCharacterBase::SetDead()
{
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	PlayDeadAnimation();
	SetActorEnableCollision(false);
	HealthBar->SetHiddenInGame(true);
}

void ACPCharacterBase::PlayDeadAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(DeadMontage);
}

void ACPCharacterBase::AttackHitCheck()
{
	FHitResult HitResult;
	const FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	const float AttackRange = 40.0f;
	const float AttackRadius = 50.0f;
	const float AttackDamage = 30.0f;
	const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + GetActorForwardVector() * AttackRange;

	bool HitDetected = GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, CCHANNEL_CPACTION, FCollisionShape::MakeSphere(AttackRadius), Params);
	if (HitDetected)
	{
		FDamageEvent DamageEvent;
		HitResult.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
	}

#if ENABLE_DRAW_DEBUG
	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
	float CapsuleHalfHeight = AttackRange * 0.5f;
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight + AttackRadius, AttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);
#endif
}

void ACPCharacterBase::SetupCharacterWidget(class UCPUserWidget* UserWidget)
{
	UCPHealthBarWidget* HealthBarWidget = Cast<UCPHealthBarWidget>(UserWidget);
	if (HealthBarWidget)
	{
		HealthBarWidget->SetMaxHealth(Stat->GetMaxHealth());
		HealthBarWidget->UpdateHealthBar(Stat->GetCurrentHealth());
		Stat->OnHealthChanged.AddUObject(HealthBarWidget, &UCPHealthBarWidget::UpdateHealthBar);
	}
}
