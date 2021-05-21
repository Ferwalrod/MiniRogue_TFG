// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "MiniRogue_TFG/Characters/MonsterBase.h"
#include "MiniRogue_TFG/Characters/RogueCharacter.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "MiniRogue_TFG/Widgets/Pause.h"
#include "MiniRogue_TFG/Widgets/Inventory.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MiniRogue_TFG/Enumerates/NegativeState.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/CanvasPanel.h"
#include "Components/VerticalBox.h"
#include "MiniRogue_TFG/MyGameInstance.h"
#include "MiniRogue_TFG/PerceptionPotion.h"
#include "MiniRogue_TFG/HolyPotion.h"
#include "MiniRogue_TFG/HealthPotion.h"
#include "MiniRogue_TFG/FirePotion.h"
#include "MiniRogue_TFG/FrostPotion.h"
#include "MiniRogue_TFG/PoisonPotion.h"
#include "MiniRogue_TFG/MiniRogue_TFGGameModeBase.h"



void UInventory::NativeConstruct()
{
	Super::NativeConstruct();

	//OnClicked Buttons
	Poison_potion_Button->OnClicked.AddDynamic(this, &UInventory::OnClicked_Poison_potion_Button);
	Fire_potion_Button->OnClicked.AddDynamic(this, &UInventory::OnClicked_Fire_potion_Button);
	Frost_potion_Button->OnClicked.AddDynamic(this, &UInventory::OnClicked_Frost_potion_Button);
	Health_potion_Button->OnClicked.AddDynamic(this, &UInventory::OnClicked_Health_potion_Button);
	Holy_potion_Button->OnClicked.AddDynamic(this, &UInventory::OnClicked_Holy_potion_Button);
	Perception_potion_Button->OnClicked.AddDynamic(this, &UInventory::OnClicked_Perception_potion_Button);
	BTN_Close_Inventory->OnClicked.AddDynamic(this, &UInventory::OnClicked_BTN_Close_Inventory);
	BTN_Weapon->OnClicked.AddDynamic(this, &UInventory::OnClicked_BTN_Weapon);

	//On hovered or unhovered buttons

	exp_button->OnHovered.AddDynamic(this, &UInventory::OnHovered_Exp_Button);
	exp_button->OnUnhovered.AddDynamic(this, &UInventory::OnUnhovered_Exp_Button);
	Health_button->OnHovered.AddDynamic(this, &UInventory::OnHovered_Health_Button);
	Health_button->OnUnhovered.AddDynamic(this, &UInventory::OnUnhovered_Health_Button);
	Food_Button->OnHovered.AddDynamic(this, &UInventory::OnHovered_Food_Button);
	Food_Button->OnUnhovered.AddDynamic(this, &UInventory::OnUnhovered_Food_Button);
	Armor_button->OnHovered.AddDynamic(this, &UInventory::OnHovered_Armor_Button);
	Armor_button->OnUnhovered.AddDynamic(this, &UInventory::OnUnhovered_Armor_Button);
	Gold_button->OnHovered.AddDynamic(this, &UInventory::OnHovered_Gold_Button);
	Gold_button->OnUnhovered.AddDynamic(this, &UInventory::OnUnhovered_Gold_Button);
	Curse_State->OnHovered.AddDynamic(this, &UInventory::OnHovered_Curse_State);
	Curse_State->OnUnhovered.AddDynamic(this, &UInventory::OnUnhovered_Curse_State);
	Poisoned_state->OnHovered.AddDynamic(this, &UInventory::OnHovered_Poisoned_State);
	Poisoned_state->OnUnhovered.AddDynamic(this, &UInventory::OnUnhovered_Poisoned_State);
	Blinded_state->OnHovered.AddDynamic(this, &UInventory::OnHovered_Blinded_State);
	Blinded_state->OnUnhovered.AddDynamic(this, &UInventory::OnUnhovered_Blinded_State);
	Perceptive_state->OnHovered.AddDynamic(this, &UInventory::OnHovered_Perceptive_State);
	Perceptive_state->OnUnhovered.AddDynamic(this, &UInventory::OnUnhovered_Perceptive_State);
	Poison_potion_Button->OnHovered.AddDynamic(this, &UInventory::OnHovered_Poison_potion_Button);
	Poison_potion_Button->OnUnhovered.AddDynamic(this, &UInventory::OnUnhovered_Poison_potion_Button);
	Fire_potion_Button->OnHovered.AddDynamic(this, &UInventory::OnHovered_Fire_potion_Button);
	Fire_potion_Button->OnUnhovered.AddDynamic(this, &UInventory::OnUnhovered_Fire_potion_Button);
	Frost_potion_Button->OnHovered.AddDynamic(this, &UInventory::OnHovered_Frost_potion_Button);
	Frost_potion_Button->OnUnhovered.AddDynamic(this, &UInventory::OnUnhovered_Frost_potion_Button);
	Health_potion_Button->OnHovered.AddDynamic(this, &UInventory::OnHovered_Health_potion_Button);
	Health_potion_Button->OnUnhovered.AddDynamic(this, &UInventory::OnUnhovered_Health_potion_Button);
	Holy_potion_Button->OnHovered.AddDynamic(this, &UInventory::OnHovered_Holy_potion_Button);
	Holy_potion_Button->OnUnhovered.AddDynamic(this, &UInventory::OnUnhovered_Holy_potion_Button);
	Perception_potion_Button->OnHovered.AddDynamic(this, &UInventory::OnHovered_Perception_potion_Button);
	Perception_potion_Button->OnUnhovered.AddDynamic(this, &UInventory::OnUnhovered_Perception_potion_Button);

	
}

void UInventory::NativeTick(const FGeometry& Geometry, float DeltaTime)
{
	Super::NativeTick(Geometry, DeltaTime);
}

void UInventory::UpdateInterface() {

	TXT_Health_Value->SetText(UKismetTextLibrary::Conv_IntToText(PlayerCharacter->Health));
	float health = UKismetMathLibrary::Conv_IntToFloat(PlayerCharacter->Health);
	float maxHealth = UKismetMathLibrary::Conv_IntToFloat(PlayerCharacter->MaxHealth);
	Health_bar->SetPercent(health / maxHealth);
	TXT_Exp_Value->SetText(UKismetTextLibrary::Conv_IntToText(PlayerCharacter->Exp));
	float exp = UKismetMathLibrary::Conv_IntToFloat(PlayerCharacter->Exp);
	float maxExp = UKismetMathLibrary::Conv_IntToFloat(PlayerCharacter->MaxExp);
	Experience_bar->SetPercent(exp / maxExp);
	TXT_Armor_Value->SetText(UKismetTextLibrary::Conv_IntToText(PlayerCharacter->Armor));
	float armor = UKismetMathLibrary::Conv_IntToFloat(PlayerCharacter->Armor);
	float maxArmor = UKismetMathLibrary::Conv_IntToFloat(PlayerCharacter->MaxArmor);
	Armor_bar->SetPercent(armor / maxArmor);
	TXT_Food_Value->SetText(UKismetTextLibrary::Conv_IntToText(PlayerCharacter->Food));
	float food = UKismetMathLibrary::Conv_IntToFloat(PlayerCharacter->Food);
	float maxFood = UKismetMathLibrary::Conv_IntToFloat(PlayerCharacter->MaxFood);
	Food_bar->SetPercent(food / maxFood);
	TXT_Gold_Value->SetText(UKismetTextLibrary::Conv_IntToText(PlayerCharacter->Gold));
	float gold = UKismetMathLibrary::Conv_IntToFloat(PlayerCharacter->Gold);
	float maxGold = UKismetMathLibrary::Conv_IntToFloat(PlayerCharacter->MaxGold);
	Gold_bar->SetPercent(gold / maxGold);

	UpdatePlayerStates();
	UpdatePotions();
	UpdateWeapons();
}

void UInventory::SetPlayerCharacter(ABaseCharacter* Player)
{
	PlayerCharacter = Player;
}

void UInventory::UpdatePlayerStates()
{
	if (PlayerCharacter->States.Contains(ENegativeState::Cursed)) {
		Curse_State->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		Curse_State->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (PlayerCharacter->States.Contains(ENegativeState::Poisoned)) {
		Poisoned_state->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		Poisoned_state->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (PlayerCharacter->States.Contains(ENegativeState::Blinded)) {
		Blinded_state->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		Blinded_state->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (PlayerCharacter->PositiveStates.Contains(EPositiveState::Perceptive)) {
		Perceptive_state->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		Perceptive_state->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UInventory::UpdatePotions()
{
	Fire_potion_amount->SetText(FText::FromString("0"));
	Frost_potion_amount->SetText(FText::FromString("0"));
	Poison_potion_amount->SetText(FText::FromString("0"));
	Health_potion_amount->SetText(FText::FromString("0"));
	Perception_potion_amount->SetText(FText::FromString("0"));
	Sacred_potion_amount->SetText(FText::FromString("0"));
	for (int i = 0; i < PlayerCharacter->Potions.Num(); i++) {
		if (UKismetMathLibrary::ClassIsChildOf(PlayerCharacter->Potions[i], AFirePotion::StaticClass())) {
			Fire_potion_amount->SetText(FText::FromString("1"));
		}
		else if (UKismetMathLibrary::ClassIsChildOf(PlayerCharacter->Potions[i], AFrostPotion::StaticClass())) {
			Frost_potion_amount->SetText(FText::FromString("1"));
		}
		else if (UKismetMathLibrary::ClassIsChildOf(PlayerCharacter->Potions[i], APoisonPotion::StaticClass())) {
			Poison_potion_amount->SetText(FText::FromString("1"));
		}
		else if (UKismetMathLibrary::ClassIsChildOf(PlayerCharacter->Potions[i], AHealthPotion::StaticClass())) {
			Health_potion_amount->SetText(FText::FromString("1"));
		}
		else if (UKismetMathLibrary::ClassIsChildOf(PlayerCharacter->Potions[i], AHolyPotion::StaticClass())) {
			Sacred_potion_amount->SetText(FText::FromString("1"));
		}
		else if (UKismetMathLibrary::ClassIsChildOf(PlayerCharacter->Potions[i], APerceptionPotion::StaticClass())) {
			Perception_potion_amount->SetText(FText::FromString("1"));
		}
	}
}

void UInventory::UpdateWeapons()
{
	TXT_Weapon_Charges->SetText(UKismetTextLibrary::Conv_IntToText(PlayerCharacter->WeaponCharges));
	if (PlayerCharacter->WeaponCharges > 0) {
		switch (PlayerCharacter->currentWeapon) {
		case EWeaponType::NoWeapon:
			Wrapper_Weapon->SetVisibility(ESlateVisibility::Hidden);
			break;
		case EWeaponType::Dagger:
			IMG_Weapon->SetBrushFromTexture(SwordIco);
			Wrapper_Weapon->SetVisibility(ESlateVisibility::Visible);
			break;
		case EWeaponType::Longsword:
			IMG_Weapon->SetBrushFromTexture(SwordIco);
			Wrapper_Weapon->SetVisibility(ESlateVisibility::Visible);
			break;
		case EWeaponType::BattleAxe:
			IMG_Weapon->SetBrushFromTexture(AxeIco);
			Wrapper_Weapon->SetVisibility(ESlateVisibility::Visible);
			break;
		}
	}
	else {
		Wrapper_Weapon->SetVisibility(ESlateVisibility::Hidden);
	}
}

bool UInventory::PlayerHasPotion(ABaseCharacter* Player, EPotionType PotionType)
{
	bool res;
	switch (PotionType) {
	case EPotionType::Perception_Potion:
		res = Player->Potions.Contains(APerceptionPotion::StaticClass());
		break;
	case EPotionType::Holy_Water_Potion:
		res = Player->Potions.Contains(AHolyPotion::StaticClass());
		break;
	case EPotionType::Poison_Potion:
		res = Player->Potions.Contains(APoisonPotion::StaticClass());
		break;
	case EPotionType::Fire_Potion:
		res = Player->Potions.Contains(AFirePotion::StaticClass());
		break;
	case EPotionType::Frost_Potion:
		res = Player->Potions.Contains(AFrostPotion::StaticClass());
		break;
	case EPotionType::Health_Potion:
		res = Player->Potions.Contains(AHealthPotion::StaticClass());
		break;
	}
	return res;
}

void UInventory::UsePotionInventory(ABaseCharacter* Player, EPotionType PotionType)
{
	AMonsterBase* Enemy;
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
	APerceptionPotion* PerceptionPotion;
	AHolyPotion* HolyPotion;
	APoisonPotion* PoisonPotion;
	AFirePotion* FirePotion;
	AFrostPotion* FrostPotion;
	AHealthPotion* HealthPotion;
	switch (PotionType) {
	case EPotionType::Perception_Potion:
		PerceptionPotion = GetWorld()->SpawnActor<APerceptionPotion>(APerceptionPotion::StaticClass(), Player->GetActorLocation(), FRotator(0.f, 0.f, 0.f));
		PerceptionPotion->UsePotion(Player, nullptr);
		PerceptionPotion->Destroy();
		break;
	case EPotionType::Holy_Water_Potion:
		HolyPotion = GetWorld()->SpawnActor<AHolyPotion>(AHolyPotion::StaticClass(), Player->GetActorLocation(), FRotator(0.f, 0.f, 0.f));
		HolyPotion->UsePotion(Player, nullptr);
		HolyPotion->Destroy();
		break;
	case EPotionType::Poison_Potion:
		if (GI) {
			if (GI->ActMonster) {
				Enemy = GI->ActMonster;
				PoisonPotion = GetWorld()->SpawnActor<APoisonPotion>(APoisonPotion::StaticClass(), Player->GetActorLocation(), FRotator(0.f, 0.f, 0.f));
				PoisonPotion->UsePotion(Player, Enemy);
				PoisonPotion->Destroy();
			}
			else if (GI->ActBoss) {
				Enemy = GI->ActBoss;
				PoisonPotion = GetWorld()->SpawnActor<APoisonPotion>(APoisonPotion::StaticClass(), Player->GetActorLocation(), FRotator(0.f, 0.f, 0.f));
				PoisonPotion->UsePotion(Player, Enemy);
				PoisonPotion->Destroy();
			}
		}
		break;
	case EPotionType::Fire_Potion:
		if (GI) {
			if (GI->ActMonster) {
				Enemy = GI->ActMonster;
				FirePotion = GetWorld()->SpawnActor<AFirePotion>(AFirePotion::StaticClass(), Player->GetActorLocation(), FRotator(0.f, 0.f, 0.f));
				FirePotion->UsePotion(Player, Enemy);
				FirePotion->Destroy();
			}
			else if (GI->ActBoss) {
				Enemy = GI->ActBoss;
				FirePotion = GetWorld()->SpawnActor<AFirePotion>(AFirePotion::StaticClass(), Player->GetActorLocation(), FRotator(0.f, 0.f, 0.f));
				FirePotion->UsePotion(Player, Enemy);
				FirePotion->Destroy();
			}
		}
		break;
	case EPotionType::Frost_Potion:
		if (GI) {
			if (GI->ActMonster) {
				Enemy = GI->ActMonster;
				FrostPotion = GetWorld()->SpawnActor<AFrostPotion>(AFrostPotion::StaticClass(), Player->GetActorLocation(), FRotator(0.f, 0.f, 0.f));
				FrostPotion->UsePotion(Player, Enemy);
				FrostPotion->Destroy();
			}
			else if (GI->ActBoss) {
				Enemy = GI->ActBoss;
				FrostPotion = GetWorld()->SpawnActor<AFrostPotion>(AFrostPotion::StaticClass(), Player->GetActorLocation(), FRotator(0.f, 0.f, 0.f));
				FrostPotion->UsePotion(Player, Enemy);
				FrostPotion->Destroy();
			}
		}
		break;
	case EPotionType::Health_Potion:
		HealthPotion = GetWorld()->SpawnActor<AHealthPotion>(AHealthPotion::StaticClass(), Player->GetActorLocation(), FRotator(0.f, 0.f, 0.f));
		HealthPotion->UsePotion(Player, nullptr);
		HealthPotion->Destroy();
		break;
	}
}

void UInventory::OnClicked_Poison_potion_Button()
{
	if (PlayerHasPotion(PlayerCharacter, EPotionType::Poison_Potion)) {
		UsePotionInventory(PlayerCharacter, EPotionType::Poison_Potion);
		PlayerCharacter->UpdateUserInterface();
		this->UpdateInterface();
	}
}

void UInventory::OnClicked_Fire_potion_Button()
{
	if (PlayerHasPotion(PlayerCharacter, EPotionType::Fire_Potion)) {
		UsePotionInventory(PlayerCharacter, EPotionType::Fire_Potion);
		PlayerCharacter->UpdateUserInterface();
		this->UpdateInterface();
	}
}

void UInventory::OnClicked_Frost_potion_Button()
{
	if (PlayerHasPotion(PlayerCharacter, EPotionType::Frost_Potion)) {
		UsePotionInventory(PlayerCharacter, EPotionType::Frost_Potion);
		PlayerCharacter->UpdateUserInterface();
		this->UpdateInterface();
	}
}

void UInventory::OnClicked_Health_potion_Button()
{
	if (PlayerHasPotion(PlayerCharacter, EPotionType::Health_Potion)) {
		UsePotionInventory(PlayerCharacter, EPotionType::Health_Potion);
		PlayerCharacter->UpdateUserInterface();
		this->UpdateInterface();
	}
}

void UInventory::OnClicked_Holy_potion_Button()
{
	if (PlayerHasPotion(PlayerCharacter, EPotionType::Holy_Water_Potion)) {
		UsePotionInventory(PlayerCharacter, EPotionType::Holy_Water_Potion);
		PlayerCharacter->UpdateUserInterface();
		this->UpdateInterface();
	}
}

void UInventory::OnClicked_Perception_potion_Button()
{
	if (PlayerHasPotion(PlayerCharacter, EPotionType::Perception_Potion)) {
		UsePotionInventory(PlayerCharacter, EPotionType::Perception_Potion);
		PlayerCharacter->UpdateUserInterface();
		this->UpdateInterface();
	}
}

void UInventory::OnClicked_BTN_Close_Inventory()
{
	this->RemoveFromParent();
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UInventory::OnClicked_BTN_Weapon()
{
	//(TODO) IMPLEMENT WEAPONS WHEN THE ARMORY IS DONE
}

void UInventory::OnHovered_Exp_Button()
{
	DescriptionMessage = DescriptionTexts[0];
}

void UInventory::OnUnhovered_Exp_Button()
{
	DescriptionMessage = UKismetTextLibrary::Conv_StringToText("");
}

void UInventory::OnHovered_Health_Button()
{
	DescriptionMessage = DescriptionTexts[1];
}

void UInventory::OnUnhovered_Health_Button()
{
	DescriptionMessage = UKismetTextLibrary::Conv_StringToText("");
}

void UInventory::OnHovered_Food_Button()
{
	DescriptionMessage = DescriptionTexts[2];
}

void UInventory::OnUnhovered_Food_Button()
{
	DescriptionMessage = UKismetTextLibrary::Conv_StringToText("");
}

void UInventory::OnHovered_Armor_Button()
{
	DescriptionMessage = DescriptionTexts[3];
}

void UInventory::OnUnhovered_Armor_Button()
{
	DescriptionMessage = UKismetTextLibrary::Conv_StringToText("");
}

void UInventory::OnHovered_Gold_Button()
{
	DescriptionMessage = DescriptionTexts[4];
}

void UInventory::OnUnhovered_Gold_Button()
{
	DescriptionMessage = UKismetTextLibrary::Conv_StringToText("");
}

void UInventory::OnHovered_Curse_State()
{
	DescriptionMessage = DescriptionTexts[5];
}

void UInventory::OnUnhovered_Curse_State()
{
	DescriptionMessage = UKismetTextLibrary::Conv_StringToText("");
}

void UInventory::OnHovered_Poisoned_State()
{
	DescriptionMessage = DescriptionTexts[6];
}

void UInventory::OnUnhovered_Poisoned_State()
{
	DescriptionMessage = UKismetTextLibrary::Conv_StringToText("");
}

void UInventory::OnHovered_Blinded_State()
{
	DescriptionMessage = DescriptionTexts[7];
}

void UInventory::OnUnhovered_Blinded_State()
{
	DescriptionMessage = UKismetTextLibrary::Conv_StringToText("");
}

void UInventory::OnHovered_Poison_potion_Button()
{
	DescriptionMessage = DescriptionTexts[8];
}

void UInventory::OnUnhovered_Poison_potion_Button()
{
	DescriptionMessage = UKismetTextLibrary::Conv_StringToText("");
}

void UInventory::OnHovered_Fire_potion_Button()
{
	DescriptionMessage = DescriptionTexts[9];
}

void UInventory::OnUnhovered_Fire_potion_Button()
{
	DescriptionMessage = UKismetTextLibrary::Conv_StringToText("");
}

void UInventory::OnHovered_Frost_potion_Button()
{
	DescriptionMessage = DescriptionTexts[10];
}

void UInventory::OnUnhovered_Frost_potion_Button()
{
	DescriptionMessage = UKismetTextLibrary::Conv_StringToText("");
}

void UInventory::OnHovered_Health_potion_Button()
{
	DescriptionMessage = DescriptionTexts[11];
}

void UInventory::OnUnhovered_Health_potion_Button()
{
	DescriptionMessage = UKismetTextLibrary::Conv_StringToText("");
}

void UInventory::OnHovered_Holy_potion_Button()
{
	DescriptionMessage = DescriptionTexts[12];
}

void UInventory::OnUnhovered_Holy_potion_Button()
{
	DescriptionMessage = UKismetTextLibrary::Conv_StringToText("");
}

void UInventory::OnHovered_Perception_potion_Button()
{
	DescriptionMessage = DescriptionTexts[13];
}

void UInventory::OnUnhovered_Perception_potion_Button()
{
	DescriptionMessage = UKismetTextLibrary::Conv_StringToText("");
}

void UInventory::OnHovered_Perceptive_State()
{
	DescriptionMessage = DescriptionTexts[14];
}

void UInventory::OnUnhovered_Perceptive_State()
{
	DescriptionMessage = UKismetTextLibrary::Conv_StringToText("");
}
