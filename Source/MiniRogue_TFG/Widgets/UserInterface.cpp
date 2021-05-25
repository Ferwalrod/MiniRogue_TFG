// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
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
#include "Components/InvalidationBox.h"
#include "Components/VerticalBox.h"
#include "MiniRogue_TFG/Widgets/Inventory.h"
#include "MiniRogue_TFG/MyGameInstance.h"
#include "MiniRogue_TFG/PerceptionPotion.h"
#include "MiniRogue_TFG/HolyPotion.h"
#include "MiniRogue_TFG/MiniRogue_TFGGameModeBase.h"


void UUserInterface::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Pause->OnClicked.AddDynamic(this, &UUserInterface::OnClicked_Button_Pause);
	BTN_Skill_1->OnClicked.AddDynamic(this, &UUserInterface::OnClicked_BTN_Skill_1);
	BTN_Skill_2->OnClicked.AddDynamic(this, &UUserInterface::OnClicked_BTN_Skill_2);
	BTN_Map_and_Progress->OnClicked.AddDynamic(this, &UUserInterface::OnClicked_BTN_Map_And_Progress);
	Ico_Character->OnClicked.AddDynamic(this, &UUserInterface::OnClicked_Ico_Character);
	BTN_Weapon->OnClicked.AddDynamic(this, &UUserInterface::OnClicked_BTN_Weapon);

}

void UUserInterface::NativeTick(const FGeometry& Geometry, float DeltaTime)
{
	Super::NativeTick(Geometry, DeltaTime);
}

void UUserInterface::SetPlayerCharacter(ABaseCharacter* Player)
{
	PlayerCharacter = Player;
}

bool UUserInterface::IsPlayerInCombat()
{
	return PlayerCharacter->isInCombat;
}

float UUserInterface::GetExpBarPercent()
{
	float Exp = UKismetMathLibrary::Conv_IntToFloat(PlayerCharacter->Exp);
	float MaxExp = UKismetMathLibrary::Conv_IntToFloat(PlayerCharacter->MaxExp);
	return Exp / MaxExp;
}

float UUserInterface::GetHealthBarPercent()
{
	float Health = UKismetMathLibrary::Conv_IntToFloat(PlayerCharacter->Health);
	float MaxHealth = UKismetMathLibrary::Conv_IntToFloat(PlayerCharacter->MaxHealth);
	return Health / MaxHealth;
}

void UUserInterface::UpdateInterface()
{
	TXT_Armor_Count->SetText(UKismetTextLibrary::Conv_IntToText(PlayerCharacter->Armor));
	int Rank=UKismetMathLibrary::Max(PlayerCharacter->Exp/6,1);
	TXT_Exp_Count->SetText(UKismetTextLibrary::Conv_IntToText(Rank));
	TXT_Food_Count->SetText(UKismetTextLibrary::Conv_IntToText(PlayerCharacter->Food));
	TXT_Gold_Count->SetText(UKismetTextLibrary::Conv_IntToText(PlayerCharacter->Gold));
	Health_Bar->SetPercent(GetHealthBarPercent());
	Exp_Bar->SetPercent(GetExpBarPercent());
	BTN_Skill_1->SetIsEnabled(!PlayerCharacter->SkillUsed);
	BTN_Skill_2->SetIsEnabled(!PlayerCharacter->SkillUsed);
	if (PlayerCharacter->isInCombat && PlayerCharacter->WeaponCharges > 0) {
		switch (PlayerCharacter->currentWeapon) {
		case EWeaponType::NoWeapon:
			VBOX_Weapon->SetVisibility(ESlateVisibility::Hidden);
			break;
		case EWeaponType::Dagger:
			IMG_Weapon->SetBrushFromTexture(SwordTexture);
			VBOX_Weapon->SetVisibility(ESlateVisibility::Visible);
			TXT_Weapon_Charges->SetText(UKismetTextLibrary::Conv_IntToText(PlayerCharacter->WeaponCharges));
			break;
		case EWeaponType::Longsword:
			IMG_Weapon->SetBrushFromTexture(SwordTexture);
			VBOX_Weapon->SetVisibility(ESlateVisibility::Visible);
			TXT_Weapon_Charges->SetText(UKismetTextLibrary::Conv_IntToText(PlayerCharacter->WeaponCharges));
			break;
		case EWeaponType::BattleAxe:
			IMG_Weapon->SetBrushFromTexture(AxeTexture);
			VBOX_Weapon->SetVisibility(ESlateVisibility::Visible);
			TXT_Weapon_Charges->SetText(UKismetTextLibrary::Conv_IntToText(PlayerCharacter->WeaponCharges));
			break;
		}
	}
	else {
		VBOX_Weapon->SetVisibility(ESlateVisibility::Hidden);
	}
	//(TODO) === ADD CROW STUFF
}

void UUserInterface::ShowSkillsButtons()
{
	InvalidationBox_Skills->SetVisibility(ESlateVisibility::Visible);
}

void UUserInterface::HideSkillsButtons()
{
	InvalidationBox_Skills->SetVisibility(ESlateVisibility::Hidden);
}

void UUserInterface::OnClicked_Button_Pause()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	if (UMG_Pause_Ref) {
		UMG_Pause_Ref->AddToViewport();
	}
	else {
		UMG_Pause_Ref = CreateWidget<UPause>(UGameplayStatics::GetPlayerController(GetWorld(),0),PauseWidgetClass);
		UMG_Pause_Ref->AddToViewport();
	}
}

void UUserInterface::OnClicked_BTN_Skill_1()
{
	//(TODO) === ADD THE MAGE SKILLS
	ARogueCharacter* Rogue = Cast<ARogueCharacter>(PlayerCharacter);
	if (Rogue) {
		Rogue->UseBackStab();
		BTN_Skill_1->SetIsEnabled(!Rogue->SkillUsed);
		BTN_Skill_2->SetIsEnabled(!Rogue->SkillUsed);
	}

}

void UUserInterface::OnClicked_BTN_Skill_2()
{
	//(TODO) === ADD THE MAGE SKILLS
	ARogueCharacter* Rogue = Cast<ARogueCharacter>(PlayerCharacter);
	if (Rogue) {
		Rogue->UseEvasion();
		BTN_Skill_1->SetIsEnabled(!Rogue->SkillUsed);
		BTN_Skill_2->SetIsEnabled(!Rogue->SkillUsed);
	}
}

void UUserInterface::OnClicked_BTN_Map_And_Progress()
{
	//(TODO) === ADD THIS FUNCTIONALITY WHEN IMPLEMENT MAP
}

void UUserInterface::OnClicked_Ico_Character()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	if (UMG_Inventory_Ref) {
		UMG_Inventory_Ref->UpdateInterface();
		UMG_Inventory_Ref->AddToViewport();
	}
	else {
		UMG_Inventory_Ref = CreateWidget<UInventory>(UGameplayStatics::GetPlayerController(GetWorld(), 0), InventoryWidgetClass);
		UMG_Inventory_Ref->SetPlayerCharacter(PlayerCharacter);
		UMG_Inventory_Ref->UpdateInterface();
		UMG_Inventory_Ref->AddToViewport();
	}
}

void UUserInterface::OnClicked_BTN_Weapon()
{
	PlayerCharacter->UseWeaponCpp();
}
