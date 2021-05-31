// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Characters/MonsterBase.h"
#include "MiniRogue_TFG/PotionObject.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "MiniRogue_TFG/Characters/MonsterBase.h"
#include "Kismet/KismetTextLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "MiniRogue_TFG/Rooms/BossRoom.h"

UMyGameInstance::UMyGameInstance() {

}

void UMyGameInstance::NextLevelCpp()
{
	for (int i = 0; i < 8; i++) {
		LevelPool.Add(Rooms[UKismetMathLibrary::RandomIntegerInRange(0, Rooms.Num() - 1)]);
	}
}

void UMyGameInstance::InitializeFloorCpp()
{
	TSubclassOf<ABossRoom> Boss = BossRooms[UKismetMathLibrary::RandomIntegerInRange(0, BossRooms.Num() - 1)];
	ActBossRoom = Boss;
	BossRooms.Remove(Boss);
	for (int i = 0; i < 8; i++) {
		LevelPool.Add(Rooms[UKismetMathLibrary::RandomIntegerInRange(0, Rooms.Num() - 1)]);
	}
}

void UMyGameInstance::SavePlayerDataCpp(ABaseCharacter* Player)
{
	SavedData.HealthSaved = Player->Health;
	SavedData.ExpSaved = Player->Exp;
	SavedData.FoodSaved = Player->Food;
	SavedData.GoldSaved = Player->Gold;
	SavedData.ArmorSaved = Player->Armor;
	SavedData.WeaponChargesSaved = Player->WeaponCharges;
	SavedData.PotionsSaved = Player->Potions;
	SavedData.NegativeStatesSaved = Player->States;
	SavedData.PositiveStatesSaved = Player->PositiveStates;
	SavedData.NextSuccess = Player->NextSuccess;
	SavedData.SkillUsed = Player->SkillUsed;
}

void UMyGameInstance::LoadPlayerDataCpp(ABaseCharacter* Player)
{
	Player->Health = SavedData.HealthSaved;
	Player->Exp = SavedData.ExpSaved;
	Player->Food = SavedData.FoodSaved;
	Player->Gold = SavedData.GoldSaved;
	Player->Armor = SavedData.ArmorSaved;
	Player->WeaponCharges = SavedData.WeaponChargesSaved;
	Player->Potions = SavedData.PotionsSaved;
	Player->States = SavedData.NegativeStatesSaved;
	Player->PositiveStates = SavedData.PositiveStatesSaved;
	Player->NextSuccess = SavedData.NextSuccess;
	Player->SkillUsed = SavedData.SkillUsed;
}

void UMyGameInstance::InitializeRoguePlayerCpp(ABaseCharacter* Player)
{
	Player->Health = RogueInitialStats.HealthSaved;
	Player->Exp = RogueInitialStats.ExpSaved;
	Player->Food = RogueInitialStats.FoodSaved;
	Player->Gold = RogueInitialStats.GoldSaved;
	Player->Armor = RogueInitialStats.ArmorSaved;
	Player->WeaponCharges = RogueInitialStats.WeaponChargesSaved;
	Player->Potions = RogueInitialStats.PotionsSaved;
	Player->States = RogueInitialStats.NegativeStatesSaved;
	Player->PositiveStates = RogueInitialStats.PositiveStatesSaved;
	Player->NextSuccess = RogueInitialStats.NextSuccess;
	Player->SkillUsed = RogueInitialStats.SkillUsed;
}

void UMyGameInstance::InitializeMagePlayerCpp(ABaseCharacter* Player)
{
	Player->Health = MageInitialStats.HealthSaved;
	Player->Exp = MageInitialStats.ExpSaved;
	Player->Food = MageInitialStats.FoodSaved;
	Player->Gold = MageInitialStats.GoldSaved;
	Player->Armor = MageInitialStats.ArmorSaved;
	Player->WeaponCharges = MageInitialStats.WeaponChargesSaved;
	Player->Potions = MageInitialStats.PotionsSaved;
	Player->States = MageInitialStats.NegativeStatesSaved;
	Player->PositiveStates = MageInitialStats.PositiveStatesSaved;
	Player->NextSuccess = MageInitialStats.NextSuccess;
	Player->SkillUsed = MageInitialStats.SkillUsed;
}

void UMyGameInstance::AddRoomToHistoryCpp()
{
	if (RoomIndex == 0) {
		VisitedRooms.Empty(8);
		VisitedRooms.Add(RoomIndex);
	}
	else {
		VisitedRooms.Add(RoomIndex);
	}
}
