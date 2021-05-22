// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmoryInteraction.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "Components/Button.h"
#include "Kismet/KismetTextLibrary.h"
#include "MiniRogue_TFG/WeaponType.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "MiniRogue_TFG/Dice.h"
#include "MiniRogue_TFG/MyGameInstance.h"
#include "MiniRogue_TFG/MiniRogue_TFGGameModeBase.h"

void UArmoryInteraction::NativeConstruct()
{
	Super::NativeConstruct();
	BTN_Accept->OnClicked.AddDynamic(this, &UArmoryInteraction::OnClicked_Button_Accept);
}

void UArmoryInteraction::NativeTick(const FGeometry& Geometry, float DeltaTime)
{
	Super::NativeTick(Geometry, DeltaTime);

}
void UArmoryInteraction::OnClicked_Button_Accept()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Controller->bEnableClickEvents = true;
	RemoveDices();
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	this->RemoveFromParent();
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
void UArmoryInteraction::RemoveDices()
{
	TArray<AActor*> playerDices;
	//auto PlayerDiceClass = ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/PlayerDice.PlayerDice'"));
	if (PlayerDiceClass) {
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerDiceClass, playerDices);
	}
	if (playerDices.Num() != 0) {
		for (int i = 0; i < playerDices.Num(); i++) {
			playerDices[i]->Destroy();
		}
	}
	TArray<AActor*> dungeonDices;
	//auto DungeonDiceClass= ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/DungeonDice.DungeonDice''"));
	if (DungeonDiceClass) {
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), DungeonDiceClass, dungeonDices);
	}
	if (dungeonDices.Num() != 0) {
		for (int j = 0; j < dungeonDices.Num(); j++) {
			dungeonDices[j]->Destroy();
		}
	}
}
void UArmoryInteraction::Setup(int NumReward) {
	ABaseCharacter* Character = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Character) {
		PlayerCharacter = Character;
		switch (NumReward - 1) {
		case 0:
			PlayerCharacter->EquiptWeaponCpp(EWeaponType::Dagger);
			TXT_Reward_String = FString(TEXT("Rusty Dagger"));
			IMG_Weapon->SetBrushFromTexture(SwordIco);
			break;
		case 1:
			PlayerCharacter->EquiptWeaponCpp(EWeaponType::Dagger);
			TXT_Reward_String = FString(TEXT("Rusty Dagger"));
			IMG_Weapon->SetBrushFromTexture(SwordIco);
			break;
		case 2:
			PlayerCharacter->EquiptWeaponCpp(EWeaponType::Dagger);
			TXT_Reward_String = FString(TEXT("Rusty Dagger"));
			IMG_Weapon->SetBrushFromTexture(SwordIco);
			break;
		case 3:
			PlayerCharacter->EquiptWeaponCpp(EWeaponType::Longsword);
			TXT_Reward_String = FString(TEXT("Fair LongSword"));
			IMG_Weapon->SetBrushFromTexture(SwordIco);
			break;
		case 4:
			PlayerCharacter->EquiptWeaponCpp(EWeaponType::Longsword);
			TXT_Reward_String = FString(TEXT("Fair LongSword"));
			IMG_Weapon->SetBrushFromTexture(SwordIco);
			break;
		case 5:
			PlayerCharacter->EquiptWeaponCpp(EWeaponType::BattleAxe);
			TXT_Reward_String = FString(TEXT("Pristine Battle Axe"));
			IMG_Weapon->SetBrushFromTexture(AxeIco);
			break;
		}
		PlayerCharacter->UpdateUserInterface();
	}
}
