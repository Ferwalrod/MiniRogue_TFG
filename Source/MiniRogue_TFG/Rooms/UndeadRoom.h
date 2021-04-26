// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniRogue_TFG/Rooms/MonsterRoom.h"
#include "UndeadRoom.generated.h"

/**
 * 
 */
UCLASS()
class MINIROGUE_TFG_API AUndeadRoom : public AMonsterRoom
{
	GENERATED_BODY()

public:
	AUndeadRoom();

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	
};
