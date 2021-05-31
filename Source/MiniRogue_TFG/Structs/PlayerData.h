// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MiniRogue_TFG/Enumerates/NegativeState.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "PlayerData.generated.h"

class APotionObject;


USTRUCT(BlueprintType)
struct MINIROGUE_TFG_API FPlayerSavedData 
{
	GENERATED_BODY()

public:
	FPlayerSavedData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int HealthSaved;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int ExpSaved;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int FoodSaved;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int GoldSaved;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int ArmorSaved;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int WeaponChargesSaved;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		TArray<TSubclassOf<APotionObject>> PotionsSaved;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		TSet<TEnumAsByte<ENegativeState>> NegativeStatesSaved;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		TSet<TEnumAsByte<EPositiveState>> PositiveStatesSaved;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		bool NextSuccess;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		bool SkillUsed;

};
