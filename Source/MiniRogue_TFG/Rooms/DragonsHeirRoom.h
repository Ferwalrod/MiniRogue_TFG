// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniRogue_TFG/Rooms/BossRoom.h"
#include "DragonsHeirRoom.generated.h"

/**
 * 
 */
UCLASS()
class MINIROGUE_TFG_API ADragonsHeirRoom : public ABossRoom
{
	GENERATED_BODY()

public:
	ADragonsHeirRoom();

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;


	
};
