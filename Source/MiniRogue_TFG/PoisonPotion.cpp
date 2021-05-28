// Fill out your copyright notice in the Description page of Project Settings.


#include "PoisonPotion.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "MiniRogue_TFG/Characters/MonsterBase.h"


APoisonPotion::APoisonPotion() {

}
void APoisonPotion::BeginPlay()
{
	Super::BeginPlay();
}

void APoisonPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APoisonPotion::UsePotion(ACharacter* User, ACharacter* Target)
{
	ABaseCharacter* Player = Cast<ABaseCharacter>(User);
	if (Player) {
		if (Player->Potions.Contains(this->GetClass())) {
			AMonsterBase* Monster = Cast<AMonsterBase>(Target);
			if (Monster) {
				Monster->NegativeStates.Add(ENegativeState::Poisoned);
				Player->Potions.Remove(this->GetClass());
			}
		}
	}
}
