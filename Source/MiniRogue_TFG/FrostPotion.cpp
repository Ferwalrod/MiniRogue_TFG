// Fill out your copyright notice in the Description page of Project Settings.


#include "FrostPotion.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "MiniRogue_TFG/Characters/MonsterBase.h"

AFrostPotion::AFrostPotion() {

}
void AFrostPotion::BeginPlay()
{
	Super::BeginPlay();
}

void AFrostPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFrostPotion::UsePotion(ACharacter* User, ACharacter* Target)
{
	ABaseCharacter* Player = Cast<ABaseCharacter>(User);
	if (Player) {
		if (Player->Potions.Contains(this->GetClass())) {
			AMonsterBase* Monster = Cast<AMonsterBase>(Target);
			if (Monster) {
				Monster->NegativeStates.Add(ENegativeState::Frozen);
				Player->Potions.Remove(this->GetClass());
			}
		}
	}

}
