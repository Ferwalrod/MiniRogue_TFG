// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RogueAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MINIROGUE_TFG_API URogueAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

	URogueAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly, Category="AnimVariables")
	bool isMoving;
	
};
