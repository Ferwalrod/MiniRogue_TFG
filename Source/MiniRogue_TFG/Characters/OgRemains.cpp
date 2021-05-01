// Fill out your copyright notice in the Description page of Project Settings.


#include "OgRemains.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "Animation/AnimSequence.h"
#include "MiniRogue_TFG/MyGameInstance.h"
#include "MiniRogue_TFG/Widgets/MonsterState.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Components/WidgetComponent.h"

// Sets default values
AOgRemains::AOgRemains()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AOgRemains::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOgRemains::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOgRemains::UpdateOgState()
{
	if (NegativeStates.Contains(ENegativeState::Poisoned)) {
		Live -= 4;
	}
	if (Live <= 0) {
		if (PhaseNumber == 2) {
			IsDead = true;
		}
		else {
			InitializePhase2();
		}
	}
}

void AOgRemains::InitializePhase1()
{
	PhaseNumber = 1;
	FMonsterLevelStruct Level = OgPhases[0];
	Live = Level.Live;
	MaxMonsterLive = Live;
	EnemyMesh = Level.EnemyMesh;
	AnimIdle = Level.AnimIdle;
	AnimCombat = Level.AnimCombat;
	AnimDead = Level.AnimDead;
	this->GetMesh()->SetAnimation(AnimIdle);
	this->GetMesh()->SetMaterial(0, Level.MonsterMat);
	Damage = Level.Damage;
	DamageType = Level.DamageType;
	Reward = Level.Reward;
	MonsterName = Level.MonsterName;
}

void AOgRemains::InitializePhase2()
{
	NegativeStates.Empty();
	PhaseNumber = 2;
	FMonsterLevelStruct Level = OgPhases[1];
	Live = Level.Live;
	MaxMonsterLive = Live;
	EnemyMesh = Level.EnemyMesh;
	AnimIdle = Level.AnimIdle;
	AnimCombat = Level.AnimCombat;
	AnimDead = Level.AnimDead;
	this->GetMesh()->SetAnimation(AnimIdle);
	this->GetMesh()->SetMaterial(0, Level.MonsterMat);
	Damage = Level.Damage;
	DamageType = Level.DamageType;
	Reward = Level.Reward;
	MonsterName = Level.MonsterName;
}

// Called to bind functionality to input
void AOgRemains::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

