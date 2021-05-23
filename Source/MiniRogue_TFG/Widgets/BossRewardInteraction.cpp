// Fill out your copyright notice in the Description page of Project Settings.


#include "BossRewardInteraction.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MiniRogue_TFG/HolyPotion.h"
#include "MiniRogue_TFG/FirePotion.h"
#include "MiniRogue_TFG/FrostPotion.h"
#include "MiniRogue_TFG/PoisonPotion.h"
#include "MiniRogue_TFG/PerceptionPotion.h"
#include "MiniRogue_TFG/FirePotion.h"
#include "MiniRogue_TFG/HealthPotion.h"
#include "Components/Image.h"
#include "MiniRogue_TFG/MiniRogue_TFGGameModeBase.h"
#include "MiniRogue_TFG/Widgets/TreasureInteraction2.h"
#include "Engine/World.h"
#include "Engine/Texture2D.h"
#include "MiniRogue_TFG/MyGameInstance.h"
#include "GameFramework/PlayerController.h"

void UBossRewardInteraction::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Accept->OnClicked.AddDynamic(this, &UBossRewardInteraction::OnClicked_Accept_Button);
	Button_Reward_Left->OnClicked.AddDynamic(this, &UBossRewardInteraction::OnClicked_Left_Reward_Button);
	Button_Reward_Right->OnClicked.AddDynamic(this, &UBossRewardInteraction::OnClicked_Right_Reward_Button);

	RewardChoose = getRandomReward();
	LeftReward = UKismetTextLibrary::Conv_TextToString(RewardChoose.Left);
	RightReward = UKismetTextLibrary::Conv_TextToString(RewardChoose.Right);
	ChangeImage(RewardChoose.Left, IMG_Reward_Left);
	ChangeImage(RewardChoose.Right, IMG_Reward_Right);
}

void UBossRewardInteraction::NativeTick(const FGeometry& Geometry, float DeltaTime)
{
	Super::NativeTick(Geometry, DeltaTime);
}

FRewardOption UBossRewardInteraction::getRandomReward()
{
	return Rewards[UKismetMathLibrary::RandomInteger(6)];
}

void UBossRewardInteraction::ChangeImage(FText Text, UImage* Image)
{
	FString Option = UKismetTextLibrary::Conv_TextToString(Text);
	if (Option.Equals(FString(TEXT("+1 ARMOR")))) {
		Image->SetBrushFromTexture(ArmorIco);
	}
	else if (Option.Equals(FString(TEXT("+2 EXP")))) {
		Image->SetBrushFromTexture(ExpIco);
	}
	else if (Option.Equals(FString(TEXT("+1 GOLD")))) {
		Image->SetBrushFromTexture(GoldIco);
	}
	else if (Option.Equals(FString(TEXT("PERCEPTION POTION")))) {
		Image->SetBrushFromTexture(PerceptionIco);
	}
	else if (Option.Equals(FString(TEXT("FROST POTION")))) {
		Image->SetBrushFromTexture(FrostIco);
	}
	else if (Option.Equals(FString(TEXT("FIRE POTION")))) {
		Image->SetBrushFromTexture(FireIco);
	}
	else if (Option.Equals(FString(TEXT("HEALING POTION")))) {
		Image->SetBrushFromTexture(HealthIco);
	}
	else if (Option.Equals(FString(TEXT("POISON POTION")))) {
		Image->SetBrushFromTexture(PoisonIco);
	}
	else if (Option.Equals(FString(TEXT("HOLY WATER POTION")))) {
		Image->SetBrushFromTexture(HolyIco);
	}
	
}

void UBossRewardInteraction::ApplyReward(ABaseCharacter* Player, FText RewardChoice)
{
	FString Option = UKismetTextLibrary::Conv_TextToString(RewardChoice);
	if (Option.Equals(FString(TEXT("+1 ARMOR")))) {
		Player->Armor = UKismetMathLibrary::Clamp(Player->Armor + 1, 0, Player->MaxArmor);
	}
	else if (Option.Equals(FString(TEXT("+2 EXP")))) {
		Player->Exp = UKismetMathLibrary::Clamp(Player->Exp + 2, 0, Player->MaxExp);
	}
	else if (Option.Equals(FString(TEXT("+1 GOLD")))) {
		Player->Gold = UKismetMathLibrary::Clamp(Player->Gold + 1, 0, Player->MaxGold);
	}
	else if (Option.Equals(FString(TEXT("PERCEPTION POTION")))) {
		if (Player->Potions.Num() < 2 && !Player->Potions.Contains(APerceptionPotion::StaticClass())) {
			Player->Potions.Add(APerceptionPotion::StaticClass());
		}
	}
	else if (Option.Equals(FString(TEXT("FROST POTION")))) {
		if (Player->Potions.Num() < 2 && !Player->Potions.Contains(AFrostPotion::StaticClass())) {
			Player->Potions.Add(AFrostPotion::StaticClass());
		}
	}
	else if (Option.Equals(FString(TEXT("FIRE POTION")))) {
		if (Player->Potions.Num() < 2 && !Player->Potions.Contains(AFirePotion::StaticClass())) {
			Player->Potions.Add(AFirePotion::StaticClass());
		}
	}
	else if (Option.Equals(FString(TEXT("HEALING POTION")))) {
		if (Player->Potions.Num() < 2 && !Player->Potions.Contains(AHealthPotion::StaticClass())) {
			Player->Potions.Add(AHealthPotion::StaticClass());
		}
	}
	else if (Option.Equals(FString(TEXT("POISON POTION")))) {
		if (Player->Potions.Num() < 2 && !Player->Potions.Contains(AHealthPotion::StaticClass())) {
			Player->Potions.Add(AHealthPotion::StaticClass());
		}
	}
	else if (Option.Equals(FString(TEXT("HOLY WATER POTION")))) {
		if (Player->Potions.Num() < 2 && !Player->Potions.Contains(AHolyPotion::StaticClass())) {
			Player->Potions.Add(AHolyPotion::StaticClass());
		}
	}
}

void UBossRewardInteraction::OnClicked_Accept_Button()
{
	ABaseCharacter* Player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player) {
		if (Reward1Selected) {
			ApplyReward(Player, RewardChoose.Left);
			this->RemoveFromParent();
			UGameplayStatics::SetGamePaused(GetWorld(), false);
			Player->UpdateUserInterface();
		}
		else {
			ApplyReward(Player, RewardChoose.Right);
			this->RemoveFromParent();
			UGameplayStatics::SetGamePaused(GetWorld(), false);
			Player->UpdateUserInterface();
		}
	}
}

void UBossRewardInteraction::OnClicked_Left_Reward_Button()
{
	Reward1Selected = true;
	Img_right_border_seleccted->SetVisibility(ESlateVisibility::Hidden);
	Img_left_border_seleccted->SetVisibility(ESlateVisibility::Visible);
}

void UBossRewardInteraction::OnClicked_Right_Reward_Button()
{
	Reward1Selected = false;
	Img_right_border_seleccted->SetVisibility(ESlateVisibility::Visible);
	Img_left_border_seleccted->SetVisibility(ESlateVisibility::Hidden);
}
