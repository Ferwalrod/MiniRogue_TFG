// Fill out your copyright notice in the Description page of Project Settings.


#include "ShrineInteraction2.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MiniRogue_TFG/Widgets/ShrineInteraction2.h"
#include "Kismet/KismetTextLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "MiniRogue_TFG/Dice.h"
#include "Engine/World.h"
#include "MiniRogue_TFG/MiniRogue_TFGGameModeBase.h"
#include "MiniRogue_TFG/MyGameInstance.h"
#include "MiniRogue_TFG/Enumerates/NegativeState.h"
#include "Engine/Engine.h"

void UShrineInteraction2::NativeConstruct()
{
	Super::NativeConstruct();
	BTN_Accept->OnClicked.AddDynamic(this, &UShrineInteraction2::OnClicked_Button_Accept);
	ABaseCharacter* Character = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Character) {
		PlayerCharacter = Character;
		switch (DiceResult-1) {
		case 0:
			PlayerCharacter->States.Add(ENegativeState::Cursed);
			PlayerCharacter->States.Add(ENegativeState::Poisoned);
			TXT_Reward_String = "You are cursed and poisoned";
			break;
		case 1:
			PlayerCharacter->States.Add(ENegativeState::Cursed);
			TXT_Reward_String = "You are cursed";
			break;
		case 2:
			PlayerCharacter->States.Add(ENegativeState::Cursed);
			TXT_Reward_String = "You are cursed";
			break;
		case 3:
			PlayerCharacter->Health = UKismetMathLibrary::Clamp(PlayerCharacter->Health + 2, 0, PlayerCharacter->MaxHealth);
			PlayerCharacter->States.Empty(3);
			TXT_Reward_String = "Hp +2 plus negative states purged";
			break;
		case 4:
			PlayerCharacter->Health = UKismetMathLibrary::Clamp(PlayerCharacter->Health + 1, 0, PlayerCharacter->MaxHealth);
			PlayerCharacter->States.Empty(3);
			TXT_Reward_String = "Hp +1 plus negative states purged";
			break;
		case 5:
			PlayerCharacter->Health = UKismetMathLibrary::Clamp(PlayerCharacter->Health + 1, 0, PlayerCharacter->MaxHealth);
			TXT_Reward_String = "Hp +1";
			break;
		}
		PlayerCharacter->UpdateUserInterface();
		APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		Controller->bEnableClickEvents = true;
		AMiniRogue_TFGGameModeBase* GM = Cast<AMiniRogue_TFGGameModeBase>(GetWorld()->GetAuthGameMode());
		UMyGameInstance* GI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
		if (GM && GI) {
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
}

void UShrineInteraction2::NativeTick(const FGeometry& Geometry, float DeltaTime)
{
	Super::NativeTick(Geometry, DeltaTime);
}

void UShrineInteraction2::OnClicked_Button_Accept()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	this->RemoveFromParent();
}

void UShrineInteraction2::Setup(int Result)
{
	DiceResult = Result;
}

void UShrineInteraction2::DestroyDices()
{
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
