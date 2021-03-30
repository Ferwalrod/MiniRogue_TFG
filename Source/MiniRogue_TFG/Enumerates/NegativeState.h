// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NegativeState.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum ENegativeState {
	Poisoned UMETA(DisplayName="Poisoned"),
	Cursed UMETA(DisplayName="Cursed"),
	Blinded UMETA(DisplayName="Blinded"),
	Frozen UMETA(DisplayName="Frozen")
};
