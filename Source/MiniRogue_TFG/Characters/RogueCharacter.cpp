// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueCharacter.h"

ARogueCharacter::ARogueCharacter() {
	PrimaryActorTick.bCanEverTick = true;
}
void ARogueCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ARogueCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARogueCharacter::UseEvasion()
{
	if (!SkillUsed) {
		EvasionActivated = true;
		SkillUsed = true;
	}
}

void ARogueCharacter::UseBackStab()
{
	if (!SkillUsed) {
		BackStabActivated = true;
		SkillUsed = true;
	}
}
