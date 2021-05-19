// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TrapReward.generated.h"

/**
 * 
 */
UCLASS()
class MINIROGUE_TFG_API UTrapReward : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime) override;

	//Functions
	void ApplyAndShowReward(int RewardIndexRes, bool SkillTestRes);
};
