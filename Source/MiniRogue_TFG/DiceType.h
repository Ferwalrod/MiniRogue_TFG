// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DiceType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum EDiceType
{
	Player  UMETA(DisplayName = "Player"),
	Dungeon  UMETA(DisplayName = "Dungeon"),
	Curse  UMETA(DisplayName = "Curse"),
	Poison  UMETA(DisplayName = "Poison")
};
