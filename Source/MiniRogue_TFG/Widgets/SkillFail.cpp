// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillFail.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "Components/Button.h"
#include "Kismet/KismetTextLibrary.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "MiniRogue_TFG/Dice.h"
#include "MiniRogue_TFG/MyGameInstance.h"
#include "MiniRogue_TFG/MiniRogue_TFGGameModeBase.h"

void USkillFail::NativeConstruct()
{
	Super::NativeConstruct();
	ABaseCharacter* Character = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Character) {
		Player = Character;
	}
	Button_Accept->OnClicked.AddDynamic(this, &USkillFail::OnClicked_Accept);
}

void USkillFail::NativeTick(const FGeometry& Geometry, float DeltaTime)
{
	Super::NativeTick(Geometry, DeltaTime);
}

void USkillFail::RemoveDices()
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

void USkillFail::OnClicked_Accept()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Controller->bEnableClickEvents = true;
	UGameplayStatics::SetGamePaused(GetWorld(),false);
	this->RemoveFromParent();
	RemoveDices();
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
	AMiniRogue_TFGGameModeBase* GM = Cast<AMiniRogue_TFGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GI && GM) {
		GM->RoomFinished = true;
		switch (GI->RoomIndex) {
		case 0:
			Player->BottomArrowVisibility = true;
			Player->RightArrowVisibility = true;
			break;
		case 1:
			Player->BottomArrowVisibility = true;
			Player->RightArrowVisibility = true;
			break;
		case 2:
			Player->BottomArrowVisibility = true;
			break;
		case 3:
			Player->BottomArrowVisibility = true;
			Player->RightArrowVisibility = true;
			break;
		case 4:
			Player->BottomArrowVisibility = true;
			Player->RightArrowVisibility = true;
			break;
		case 5:
			Player->BottomArrowVisibility = true;
			break;
		case 6:
			Player->RightArrowVisibility = true;
			break;
		case 7:
			Player->RightArrowVisibility = true;
			break;
		}
	}
}
