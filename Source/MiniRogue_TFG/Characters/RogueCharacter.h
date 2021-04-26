// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "RogueCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MINIROGUE_TFG_API ARogueCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ARogueCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	bool BackStabActivated;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	bool EvasionActivated;
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	void UseEvasion();
	void UseBackStab();

};
