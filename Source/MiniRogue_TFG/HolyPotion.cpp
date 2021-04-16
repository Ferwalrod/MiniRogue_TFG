// Fill out your copyright notice in the Description page of Project Settings.


#include "HolyPotion.h"
#include "Characters/BaseCharacter.h"
#include "GameFramework/Character.h"

AHolyPotion::AHolyPotion() {

	PrimaryActorTick.bCanEverTick = true;
}

void AHolyPotion::BeginPlay() {
	Super::BeginPlay();
}
void AHolyPotion::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AHolyPotion::UsePotion(ACharacter* User, ACharacter* Target) {
	ABaseCharacter* Player = Cast<ABaseCharacter>(User);
	if (Player) {
		if (Player->Potions.Contains(this->GetClass())) {
			Player->States.Empty(3);
			Player->Potions.Remove(this->GetClass());
		}
	}
}