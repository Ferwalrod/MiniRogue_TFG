// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MiniRogue_TFG/Room.h"
#include "MiniRogue_TFG/Structs/PlayerData.h"
#include "MiniRogue_TFG/Rooms/BaseRoom.h"
#include "MyGameInstance.generated.h"


class AMonsterBase;
class ABaseCharacter;
class ABossRoom;


UCLASS()
class MINIROGUE_TFG_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
		
public:
	UMyGameInstance();
	
	//Attributes
	//Total de habitaciones
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Room Data")
	TArray<TSubclassOf<class ABaseRoom>> Rooms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Data")
		TArray<TSubclassOf<ABossRoom>> BossRooms;
	//Habitaciones en el nivel
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Data")
	TArray<TSubclassOf<class ABaseRoom>> LevelPool;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Room Data")
	int RoomIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
	int LevelIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
	int FloorIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
	AMonsterBase* ActMonster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
	AMonsterBase* ActBoss;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
		TSubclassOf<ABossRoom> ActBossRoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
	bool IsANewFloor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
		TArray<int> VisitedRooms;

	//Player Data
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player Saved Data")
		FPlayerSavedData  SavedData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Saved Data")
		FPlayerSavedData  RogueInitialStats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Saved Data")
		FPlayerSavedData  MageInitialStats;

	//Functions

	UFUNCTION(BlueprintCallable,Category="Data Manager")
		void NextLevelCpp();
	UFUNCTION(BlueprintCallable, Category = "Data Manager")
		void InitializeFloorCpp();
	UFUNCTION(BlueprintCallable, Category = "Data Manager")
		void SavePlayerDataCpp(ABaseCharacter* Player);
	UFUNCTION(BlueprintCallable, Category = "Data Manager")
		void LoadPlayerDataCpp(ABaseCharacter* Player);
	UFUNCTION(BlueprintCallable, Category = "Data Manager")
		void InitializeRoguePlayerCpp(ABaseCharacter* Player);
	UFUNCTION(BlueprintCallable, Category = "Data Manager")
		void InitializeMagePlayerCpp(ABaseCharacter* Player);
	UFUNCTION(BlueprintCallable, Category = "Data Manager")
		void AddRoomToHistoryCpp();
};
