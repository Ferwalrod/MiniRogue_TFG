// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponType.generated.h"
/**
 * 
 */
UENUM(BlueprintType)
enum EWeaponType
{
	NoWeapon UMETA(DisplayName = "NoWeapon"),
	Dagger UMETA(DisplayName = "Dagger"),
	Longsword UMETA(DisplayName = "LongSword"),
	BattleAxe UMETA(DisplayName = "BattleAxe")
};
