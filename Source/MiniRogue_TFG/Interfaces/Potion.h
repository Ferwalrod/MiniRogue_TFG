// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniRogue_TFG/Enumerates/PotionType.h"
#include "UObject/Interface.h"
#include "GameFramework/Character.h"
#include "Potion.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPotion : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MINIROGUE_TFG_API IPotion
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void UsePotion(ACharacter* User,ACharacter* Target) = 0;
	virtual TEnumAsByte<EPotionType> getType() = 0;
};
