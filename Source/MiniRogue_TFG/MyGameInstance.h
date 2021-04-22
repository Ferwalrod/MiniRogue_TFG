// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MiniRogue_TFG/Room.h"
#include "MyGameInstance.generated.h"


class AMonsterBase;

UCLASS()
class MINIROGUE_TFG_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
		
public:
	UMyGameInstance();
	
	//Attributes
	//Total de habitaciones
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Room Data")
	TArray<TSubclassOf<class ARoom>> Rooms;
	//Habitaciones en el nivel
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Data")
	TArray<TSubclassOf<class ARoom>> LevelPool;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Room Data")
	int RoomIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
	int LevelIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
	int FloorIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
	AMonsterBase* ActMonster;

	void PassLevel();
	void PassFloor();
	//Guardar los datos del juegador TODO
};
