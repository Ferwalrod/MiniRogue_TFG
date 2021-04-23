// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "Animation/AnimSequence.h"
#include "MiniRogue_TFG/MyGameInstance.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Components/WidgetComponent.h"

// Sets default values
AMonsterBase::AMonsterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);

}

// Called when the game starts or when spawned
void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterBase::InitializeMonster()
{
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	if (GI) {
		Floor = GI->FloorIndex;
		FMonsterLevelStruct EnemyLevel = MonsterLevel[Floor];
		EnemyMesh = EnemyLevel.EnemyMesh;
		AnimIdle = EnemyLevel.AnimIdle;
		AnimCombat = EnemyLevel.AnimCombat;
		AnimDead = EnemyLevel.AnimDead;
		this->GetMesh()->SetAnimation(AnimIdle);
		this->GetMesh()->SetMaterial(0,EnemyLevel.MonsterMat);
		Damage = EnemyLevel.Damage;
		DamageType = EnemyLevel.DamageType;
		Reward = EnemyLevel.Reward;
		MonsterName = EnemyLevel.MonsterName;
	}

	//I need the widget c++ class to continue
	//...
}

void AMonsterBase::UpdateMonsterState()
{
	if (NegativeStates.Contains(ENegativeState::Frozen)) {
		NegativeStates.Remove(NegativeStates.FindId(ENegativeState::Frozen));
		IsMonsterFrozen = true;
	}
	else {
		IsMonsterFrozen = false;
	}
	if (NegativeStates.Contains(ENegativeState::Poisoned)) {
		Live = Live - 4;
	}
	if (Live <= 0) {
		IsDead = true;
	}
}

// Called to bind functionality to input
void AMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

