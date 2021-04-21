// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PotionObject.h"
#include "PoisonPotion.generated.h"

class ACharacter;

UCLASS()
class MINIROGUE_TFG_API APoisonPotion : public APotionObject
{
	GENERATED_BODY()

public:
	APoisonPotion();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void UsePotion(ACharacter* User, ACharacter* Target) override;
	
};
