// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RewardOption.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct MINIROGUE_TFG_API FRewardOption 
{
	GENERATED_BODY()

public:

	FRewardOption();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		FText Left;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		FText Right;
};
