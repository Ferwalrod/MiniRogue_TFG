// Fill out your copyright notice in the Description page of Project Settings.


#include "PerceptionPotion.h"
#include "Characters/BaseCharacter.h"
#include "Enumerates/NegativeState.h"
#include "GameFramework/Character.h"

APerceptionPotion::APerceptionPotion() {
	PrimaryActorTick.bCanEverTick = true;
}

void APerceptionPotion::BeginPlay() {

	Super::BeginPlay();
}

void APerceptionPotion::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
}

void APerceptionPotion::UsePotion(ACharacter* User, ACharacter* Target) {
	ABaseCharacter* Player = Cast<ABaseCharacter>(User);
	if (Player) {
		if (Player->Potions.Contains(this->GetClass())) {
			Player->NextSuccess = true;
			Player->PositiveStates.Add(EPositiveState::Perceptive);
			Player->States.Remove(Player->States.FindId(ENegativeState::Blinded));
			Player->Potions.Remove(this->GetClass());
		}
	}
}