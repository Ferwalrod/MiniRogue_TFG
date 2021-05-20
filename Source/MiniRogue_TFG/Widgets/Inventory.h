// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

class ABaseCharacter;

UCLASS()
class MINIROGUE_TFG_API UInventory : public UUserWidget
{
	GENERATED_BODY()
public:


	void UpdateInterface();
	void SetPlayerCharacter(ABaseCharacter* Player);
};
