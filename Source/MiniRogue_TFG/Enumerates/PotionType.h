// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PotionType.generated.h"


UENUM(BlueprintType)
enum EPotionType
{
	Perception_Potion UMETA(DisplayName="Perception_Potion"),
	Holy_Water_Potion UMETA(DisplayName="Holy_Water_Potion"),
	Poison_Potion UMETA(DisplayName="Poison_Potion"),
	Fire_Potion UMETA(DisplayName="Fire_Potion"),
	Frost_Potion UMETA(DisplayName="Frost_Potion"),
	Health_Potion UMETA(DisplayName= "Health_Potion")

};
