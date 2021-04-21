// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MiniRogue_TFG/Enumerates/AttackState.h"
#include "MonsterLevelStruct.generated.h"

class USkeletalMesh;
class UAnimSequence;
class UMaterialInstanceConstant;

USTRUCT(BlueprintType)
struct MINIROGUE_TFG_API FMonsterLevelStruct 
{
	GENERATED_BODY()
public:
	FMonsterLevelStruct();

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
		int Live;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
		int Damage;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
		TEnumAsByte<EAttackState> DamageType;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
		int Reward;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
		FName MonsterName;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
		USkeletalMesh* EnemyMesh;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
		UAnimSequence* AnimIdle;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
		UAnimSequence* AnimCombat;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
		UAnimSequence* AnimDead;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
	    UMaterialInstanceConstant* MonsterMat;


	
};
