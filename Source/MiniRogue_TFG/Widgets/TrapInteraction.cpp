// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapInteraction.h"
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
#include "Components/Image.h"
#include "MiniRogue_TFG/Dice.h"
#include "MiniRogue_TFG/MyGameInstance.h"
#include "MiniRogue_TFG/MiniRogue_TFGGameModeBase.h"

void UTrapInteraction::NativeConstruct() {

	Super::NativeConstruct();

	Button_Accept->OnClicked.AddDynamic(this, &UTrapInteraction::OnClicked_Accept);
	AMiniRogue_TFGGameModeBase* gamemode = Cast<AMiniRogue_TFGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (gamemode) {
		GM = gamemode;
	}
}

void UTrapInteraction::NativeTick(const FGeometry& Geometry, float DeltaTime)
{

	Super::NativeTick(Geometry, DeltaTime);
}

void UTrapInteraction::SetDiceRespawnPoint(USphereComponent* PointRef)
{
	
}

void UTrapInteraction::ThrowDices()
{

	Controller->bEnableClickEvents = false;
	//auto PlayerDiceClass = ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/PlayerDice.PlayerDice'"));
	if (PlayerDiceClass) {
		for (int i = 0; i < PlayerLevel; i++) {
			FVector Loc = FVector(DiceRespawn->GetRelativeLocation().X, DiceRespawn->GetRelativeLocation().Y + (i * -50), DiceRespawn->GetRelativeLocation().Z);
			FRotator Rot = FRotator(UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f));
			GetWorld()->SpawnActor<AActor>(PlayerDiceClass, Loc, Rot);
		}
	}
	//auto DungeonDiceClass = ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/DungeonDice.DungeonDice'"));
	if (DungeonDiceClass) {
		FVector Loc = FVector(DiceRespawn->GetRelativeLocation().X, DiceRespawn->GetRelativeLocation().Y + 100, DiceRespawn->GetRelativeLocation().Z);
		FRotator Rot = FRotator(UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f));
		GetWorld()->SpawnActor<AActor>(DungeonDiceClass, Loc, Rot);
	}
}

void UTrapInteraction::OnClicked_Accept()
{
	this->RemoveFromParent();
	ThrowDices();
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &UTrapInteraction::CheckDiceValue, true, 0.8f);
}

void UTrapInteraction::CheckDiceValue()
{
	if (GM) {
		if (GM->Results.Num() >= 2) {
			GetWorld()->GetTimerManager().ClearTimer(Timer);
			ABaseCharacter* Player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
			if (Player) {
				if (Player->PositiveStates.Contains(EPositiveState::Perceptive)) {
					Player->PositiveStates.Remove(Player->PositiveStates.FindId(EPositiveState::Perceptive));
					SkillTestPass = true;
				}
				else {
					TArray<AActor*> PlayerDices;
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerDiceClass, PlayerDices);
					if (PlayerDices.Num() != 0) {
						for (int i = 0; i < PlayerDices.Num(); i++) {
							int DiceNumber;
							ADice* Dice = Cast<ADice>(PlayerDices[i]);
							if (*Dice->ValueMapping.Find(Dice->FaceShowing) >= 5) {
								SkillTestPass = true;
								break;
							}
						}
					}
				}

				
				TArray<AActor*> DungeonDices;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), DungeonDiceClass, DungeonDices);
				if (DungeonDices.Num() != 0) {
					UTrapReward* Widget = CreateWidget<UTrapReward>(UGameplayStatics::GetPlayerController(GetWorld(), 0), SecondWidgetClass);
					Widget->AddToViewport();
					Widget->ApplyAndShowReward(RewardChosen, SkillTestPass);
				}

			}
		}
	}
}
