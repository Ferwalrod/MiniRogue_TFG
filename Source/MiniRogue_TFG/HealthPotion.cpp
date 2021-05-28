// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPotion.h"
#include "Characters/BaseCharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

AHealthPotion::AHealthPotion() {

	PrimaryActorTick.bCanEverTick = true;
}

void AHealthPotion::BeginPlay() {

	Super::BeginPlay();
}

void AHealthPotion::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
}

void AHealthPotion::UsePotion(ACharacter* User, ACharacter* Target) {

	ABaseCharacter* Player = Cast<ABaseCharacter>(User);
	if (Player) {
		if (Player->Potions.Contains(this->GetClass())) {
			Player->Health = UKismetMathLibrary::Clamp(Player->Health + 6,0,Player->MaxHealth);
			Player->Potions.Remove(this->GetClass());
		}
	}
}