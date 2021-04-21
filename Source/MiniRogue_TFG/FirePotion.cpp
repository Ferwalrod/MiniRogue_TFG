// Fill out your copyright notice in the Description page of Project Settings.


#include "FirePotion.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "MiniRogue_TFG/Characters/MonsterBase.h"


AFirePotion::AFirePotion() {

}
void AFirePotion::BeginPlay()
{
	Super::BeginPlay();
}

void AFirePotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFirePotion::UsePotion(ACharacter* User, ACharacter* Target)
{
	ABaseCharacter* Player = Cast<ABaseCharacter>(User);
	if (Player) {
		if (Player->Potions.Contains(this->GetClass())) {
			AMonsterBase* Monster = Cast<AMonsterBase>(Target);
			if (Monster) {
				Monster->Live = Monster->Live - 7;
				Player->Potions.Remove(this->GetClass());
			}
		}
	}
}
