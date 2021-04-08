// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackState.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum EAttackState 
{
	PoisonAttack UMETA(DisplayName = "Poisoned"),
	CurseAttack UMETA(DisplayName = "Cursed"),
	BlindAttack UMETA(DisplayName = "Blinded"),
	WeaknessAttack UMETA(DisplayName="Weakness"),
	NoArmorAttack UMETA(DisplayName="NoArmor"),
	NoneStateAttack UMETA(DisplayName="NoneState")
};
