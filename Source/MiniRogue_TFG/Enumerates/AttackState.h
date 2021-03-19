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
	Poisoned UMETA(DisplayName = "Poisoned"),
	Cursed UMETA(DisplayName = "Cursed"),
	Blinded UMETA(DisplayName = "Blinded"),
	Weakness UMETA(DisplayName="Weakness"),
	NoArmor UMETA(DisplayName="NoArmor"),
	NoneState UMETA(DisplayName="NoneState")
};
