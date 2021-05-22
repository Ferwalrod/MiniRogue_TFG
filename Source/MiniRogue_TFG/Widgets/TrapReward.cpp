// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapReward.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "Components/Button.h"
#include "Components/SphereComponent.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "MiniRogue_TFG/Widgets/TrapReward.h"
#include "Kismet/GameplayStatics.h"
#include "MiniRogue_TFG/Enumerates/NegativeState.h"
#include "Components/Image.h"
#include "MiniRogue_TFG/Dice.h"
#include "MiniRogue_TFG/MyGameInstance.h"
#include "MiniRogue_TFG/PerceptionPotion.h"
#include "MiniRogue_TFG/HolyPotion.h"
#include "MiniRogue_TFG/MiniRogue_TFGGameModeBase.h"

void UTrapReward::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Accept->OnClicked.AddDynamic(this, &UTrapReward::OnClicked_Accept);
}

void UTrapReward::NativeTick(const FGeometry& Geometry, float DeltaTime)
{
	Super::NativeTick(Geometry, DeltaTime);
}

void UTrapReward::ApplyAndShowReward(int RewardIndexRes, bool SkillTestRes)
{
	RewardIndex = RewardIndexRes;
	SkillTestPass = SkillTestRes;
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
	if (GI) {
		GI->FloorIndex =this->FloorIndex;
		ABaseCharacter* Player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (Player) {
			PlayerCharacter = Player;
			PlayerHP = PlayerCharacter->Health;
			FText text;
			FString str;
			if (Player->PositiveStates.Contains(EPositiveState::Perceptive) || SkillTestPass) {
				//Reward
				if (Player->PositiveStates.Contains(EPositiveState::Perceptive)) {
					Player->PositiveStates.Remove(Player->PositiveStates.FindId(EPositiveState::Perceptive));
				}
				//Choose a trap type (AQUI en la 52 peta)
				int TrapType = UKismetMathLibrary::RandomInteger(2);
	
				switch (TrapType) {
				case 0:
					switch (RewardIndex - 1) {
					case 0:
						PlayerCharacter->Exp = UKismetMathLibrary::Clamp(PlayerCharacter->Exp + 1, 0, PlayerCharacter->MaxExp);
						 text = UKismetTextLibrary::Conv_StringToText(FString(TEXT("+1 EXP")));
						 str = FString(TEXT("EXP"));
						SetupWidget(text,str);
						break;
					case 1:
						PlayerCharacter->Exp = UKismetMathLibrary::Clamp(PlayerCharacter->Exp + 1, 0, PlayerCharacter->MaxExp);
						 text = UKismetTextLibrary::Conv_StringToText(FString(TEXT("+1 EXP")));
						 str = FString(TEXT("EXP"));
						SetupWidget(text, str);
						break;
					case 2:
						PlayerCharacter->Exp = UKismetMathLibrary::Clamp(PlayerCharacter->Exp + 2, 0, PlayerCharacter->MaxExp);
						 text = UKismetTextLibrary::Conv_StringToText(FString(TEXT("+2 EXP")));
						 str = FString(TEXT("EXP"));
						SetupWidget(text, str);
						break;
					case 3:
						PlayerCharacter->Exp = UKismetMathLibrary::Clamp(PlayerCharacter->Exp + 2, 0, PlayerCharacter->MaxExp);
					    text = UKismetTextLibrary::Conv_StringToText(FString(TEXT("+2 EXP")));
					    str = FString(TEXT("EXP"));
						SetupWidget(text, str);
						break;
					case 4:
						if (PlayerCharacter->Potions.Num() < 2 && !PlayerCharacter->Potions.Contains(APerceptionPotion::StaticClass())) {
							PlayerCharacter->Potions.Add(APerceptionPotion::StaticClass());
							text = UKismetTextLibrary::Conv_StringToText(FString(TEXT("+1 PERCEPTION POTION")));
							str = FString(TEXT("PERCEPTION"));
							SetupWidget(text, str);
						}
						break;
					case 5:
						if (PlayerCharacter->Potions.Num() < 2 && !PlayerCharacter->Potions.Contains(APerceptionPotion::StaticClass())) {
							PlayerCharacter->Potions.Add(APerceptionPotion::StaticClass());
							text = UKismetTextLibrary::Conv_StringToText(FString(TEXT("+1 PERCEPTION POTION")));
							str = FString(TEXT("PERCEPTION"));
							SetupWidget(text, str);
						}
						break;
					}
					break;
				case 1:
					switch (RewardIndex - 1) {
					case 0:
						if (PlayerCharacter->Potions.Num() < 2 && !PlayerCharacter->Potions.Contains(AHolyPotion::StaticClass())) {
							PlayerCharacter->Potions.Add(AHolyPotion::StaticClass());
							text = UKismetTextLibrary::Conv_StringToText(FString(TEXT("+1 HOLYWATER POTION")));
							str = FString(TEXT("HOLYWATER"));
							SetupWidget(text, str);
						}
						break;
					case 1:
						if (PlayerCharacter->Potions.Num() < 2 && !PlayerCharacter->Potions.Contains(AHolyPotion::StaticClass())) {
							PlayerCharacter->Potions.Add(AHolyPotion::StaticClass());
							text = UKismetTextLibrary::Conv_StringToText(FString(TEXT("+1 HOLYWATER POTION")));
							str = FString(TEXT("HOLYWATER"));
							SetupWidget(text, str);
						}
						break;
					case 2:
						PlayerCharacter->Exp = UKismetMathLibrary::Clamp(PlayerCharacter->Exp + 2, 0, PlayerCharacter->MaxExp);
						text = UKismetTextLibrary::Conv_StringToText(FString(TEXT("+2 EXP")));
						str = FString(TEXT("EXP"));
						SetupWidget(text, str);
						break;
					case 3:
						PlayerCharacter->Exp = UKismetMathLibrary::Clamp(PlayerCharacter->Exp + 2, 0, PlayerCharacter->MaxExp);
						text = UKismetTextLibrary::Conv_StringToText(FString(TEXT("+2 EXP")));
						str = FString(TEXT("EXP"));
						SetupWidget(text, str);
						break;
					case 4:
						if (PlayerCharacter->Potions.Num() < 2 && !PlayerCharacter->Potions.Contains(APerceptionPotion::StaticClass())) {
							PlayerCharacter->Potions.Add(APerceptionPotion::StaticClass());
							text = UKismetTextLibrary::Conv_StringToText(FString(TEXT("+1 PERCEPTION POTION")));
							str = FString(TEXT("PERCEPTION"));
							SetupWidget(text, str);
						}
						break;
					case 5:
						if (PlayerCharacter->Potions.Num() < 2 && !PlayerCharacter->Potions.Contains(APerceptionPotion::StaticClass())) {
							PlayerCharacter->Potions.Add(APerceptionPotion::StaticClass());
							text = UKismetTextLibrary::Conv_StringToText(FString(TEXT("+1 PERCEPTION POTION")));
							str = FString(TEXT("PERCEPTION"));
							SetupWidget(text, str);
						}
						break;
					}
					break;
				}
			}
			else {
				//Punishment
				int TrapType = UKismetMathLibrary::RandomInteger(2);
				switch (TrapType) {
				case 0:
					switch (RewardIndex - 1) {
					case 0:
						PlayerCharacter->States.Add(ENegativeState::Poisoned);
						PlayerCharacter->Health--;
						PlayerHP--;
						if (PlayerHP <= 0) {
							//(TODO) ===== SHOW GAME OVER WIDGET
						}
						else {
							text = UKismetTextLibrary::Conv_StringToText(FString(TEXT("-1 HP AND GET POISONED")));
							str = FString(TEXT("POISON"));
							SetupWidget(text, str);
						}
						break;
					case 1:
						PlayerCharacter->States.Add(ENegativeState::Poisoned);
						PlayerCharacter->Health--;
						PlayerHP--;
						if (PlayerHP <= 0) {
							//(TODO) ===== SHOW GAME OVER WIDGET
						}
						else {
							text = UKismetTextLibrary::Conv_StringToText(FString(TEXT("-1 HP AND GET POISONED")));
							str = FString(TEXT("POISON"));
							SetupWidget(text, str);
						}
						break;
					case 2:
						PlayerCharacter->Health = UKismetMathLibrary::Clamp(PlayerCharacter->Health - (FloorIndex + 1), 0, PlayerCharacter->MaxHealth);
						PlayerHP -= (FloorIndex + 1);
						if (PlayerHP <= 0) {
							//(TODO) ===== SHOW GAME OVER WIDGET
						}
						else {
							text = UKismetTextLibrary::Conv_StringToText(FString(TEXT("LOOSE HP EQUAL TO FLOOR LEVEL")));
							str = FString(TEXT("HP"));
							SetupWidget(text, str);
						}
						break;
					case 3:
						PlayerCharacter->Health = UKismetMathLibrary::Clamp(PlayerCharacter->Health - (FloorIndex + 1), 0, PlayerCharacter->MaxHealth);
						PlayerHP -= (FloorIndex + 1);
						if (PlayerHP <= 0) {
							//(TODO) ===== SHOW GAME OVER WIDGET
						}
						else {
							text = UKismetTextLibrary::Conv_StringToText(FString(TEXT("LOOSE HP EQUAL TO FLOOR LEVEL")));
							str = FString(TEXT("HP"));
							SetupWidget(text, str);
						}
						break;
					case 4:
						PlayerCharacter->Health = UKismetMathLibrary::Clamp(PlayerCharacter->Health - 3, 0, PlayerCharacter->MaxHealth);
						PlayerHP -= 3;
						if (PlayerHP <= 0) {
							//(TODO) ===== SHOW GAME OVER WIDGET
						}
						else {
							/* (TODO)
							Remove from parent
							Create loading widget
							add to viewport and Open the initialRoom
							*/
						}
						break;
					case 5:
						PlayerCharacter->Health = UKismetMathLibrary::Clamp(PlayerCharacter->Health - 3, 0, PlayerCharacter->MaxHealth);
						PlayerHP -= 3;
						if (PlayerHP <= 0) {
							//(TODO) ===== SHOW GAME OVER WIDGET
						}
						else {
							/* (TODO)
							Remove from parent
							Create loading widget
							add to viewport and Open the initialRoom
							*/
						}
						break;
					}
					break;
				case 1:
					switch (RewardIndex - 1) {
					case 0:
						PlayerCharacter->Food = UKismetMathLibrary::Clamp(PlayerCharacter->Food - (FloorIndex + 1), 0, PlayerCharacter->MaxFood);
						text = UKismetTextLibrary::Conv_StringToText(FString(TEXT("LOOSE FOOD EQUAL TO FLOOR LEVEL")));
						str = FString(TEXT("FOOD"));
						SetupWidget(text, str);
						break;
					case 1:
						PlayerCharacter->Food = UKismetMathLibrary::Clamp(PlayerCharacter->Food - (FloorIndex + 1), 0, PlayerCharacter->MaxFood);
						text = UKismetTextLibrary::Conv_StringToText(FString(TEXT("LOOSE FOOD EQUAL TO FLOOR LEVEL")));
						str = FString(TEXT("FOOD"));
						SetupWidget(text, str);
						break;
					case 2:
						PlayerCharacter->Armor = UKismetMathLibrary::Clamp(PlayerCharacter->Armor - 1, 0, PlayerCharacter->MaxArmor);
						text = UKismetTextLibrary::Conv_StringToText(FString(TEXT("LOOSE ARMOR EQUAL TO FLOOR LEVEL")));
						str = FString(TEXT("ARMOR"));
						SetupWidget(text, str);
						break;
					case 3:
						PlayerCharacter->Armor = UKismetMathLibrary::Clamp(PlayerCharacter->Armor - 1, 0, PlayerCharacter->MaxArmor);
						text = UKismetTextLibrary::Conv_StringToText(FString(TEXT("LOOSE ARMOR EQUAL TO FLOOR LEVEL")));
						str = FString(TEXT("ARMOR"));
						SetupWidget(text, str);
						break;
					case 4:
						PlayerCharacter->States.Add(ENegativeState::Poisoned);
						PlayerCharacter->Health = UKismetMathLibrary::Clamp(PlayerCharacter->Health - (FloorIndex + 1), 0, PlayerCharacter->MaxHealth);
						PlayerHP -= (FloorIndex + 1);
						if (PlayerHP <= 0) {
							//(TODO) ===== SHOW GAME OVER WIDGET
						}
						else {
							text = UKismetTextLibrary::Conv_StringToText(FString(TEXT("POISONED AND LOOSE HP EQUAL TO FLOOR LEVEL")));
							str = FString(TEXT("POISON"));
							SetupWidget(text, str);
						}
						break;
					case 5:
						PlayerCharacter->States.Add(ENegativeState::Poisoned);
						PlayerCharacter->Health = UKismetMathLibrary::Clamp(PlayerCharacter->Health - (FloorIndex + 1), 0, PlayerCharacter->MaxHealth);
						PlayerHP -= (FloorIndex + 1);
						if (PlayerHP <= 0) {
							//(TODO) ===== SHOW GAME OVER WIDGET
						}
						else {
							text = UKismetTextLibrary::Conv_StringToText(FString(TEXT("POISONED AND LOOSE HP EQUAL TO FLOOR LEVEL")));
							str = FString(TEXT("POISON"));
							SetupWidget(text, str);
						}
						break;
					}
					break;
				}
			}
			PlayerCharacter->UpdateUserInterface();
		}
	}
}

void UTrapReward::SetupWidget(FText TextReward, FString ImgReward)
{
	Text_Reward->SetText(TextReward);
	if (ImgReward.Equals(FString(TEXT("EXP")))) {
		IMG_Reward->SetBrushFromTexture(IMG_Sword);
	}
	else if (ImgReward.Equals(FString(TEXT("PERCEPTION")))) {
		IMG_Reward->SetBrushFromTexture(Perception_potion);
	}
	else if (ImgReward.Equals(FString(TEXT("HOLYWATER")))) {
		IMG_Reward->SetBrushFromTexture(Holy_Potion);
	}
	else if (ImgReward.Equals(FString(TEXT("HP")))) {
		IMG_Reward->SetBrushFromTexture(Health_ico);
	}
	else if (ImgReward.Equals(FString(TEXT("FOOD")))) {
		IMG_Reward->SetBrushFromTexture(Food_ico);
	}
	else if (ImgReward.Equals(FString(TEXT("POISON")))) {
		IMG_Reward->SetBrushFromTexture(Poisoned_ico);
	}
	else if (ImgReward.Equals(FString(TEXT("ARMOR")))) {
		IMG_Reward->SetBrushFromTexture(Armor_Ico);
	}
}

void UTrapReward::OnClicked_Accept()
{
	this->RemoveFromParent();
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Controller->bEnableClickEvents = true;
	UGameplayStatics::SetGamePaused(GetWorld(),false);
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
	AMiniRogue_TFGGameModeBase* GM = Cast<AMiniRogue_TFGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GI && GM) {
		GM->RoomFinished = true;
		switch (GI->RoomIndex) {
		case 0:
			PlayerCharacter->BottomArrowVisibility = true;
			PlayerCharacter->RightArrowVisibility = true;
			break;
		case 1:
			PlayerCharacter->BottomArrowVisibility = true;
			PlayerCharacter->RightArrowVisibility = true;
			break;
		case 2:
			PlayerCharacter->BottomArrowVisibility = true;
			break;
		case 3:
			PlayerCharacter->BottomArrowVisibility = true;
			PlayerCharacter->RightArrowVisibility = true;
			break;
		case 4:
			PlayerCharacter->BottomArrowVisibility = true;
			PlayerCharacter->RightArrowVisibility = true;
			break;
		case 5:
			PlayerCharacter->BottomArrowVisibility = true;
			break;
		case 6:
			PlayerCharacter->RightArrowVisibility = true;
			break;
		case 7:
			PlayerCharacter->RightArrowVisibility = true;
			break;
		}
	}
}
