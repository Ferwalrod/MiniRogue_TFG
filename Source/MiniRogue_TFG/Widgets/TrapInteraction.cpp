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
	ABaseCharacter* Player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player) {
		GetPlayerLevel(Player);
	}
}

void UTrapInteraction::NativeTick(const FGeometry& Geometry, float DeltaTime)
{

	Super::NativeTick(Geometry, DeltaTime);
}

void UTrapInteraction::SetDiceRespawnPoint(USphereComponent* PointRef)
{
	DiceRespawn = PointRef;
}

void UTrapInteraction::ThrowDices()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
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
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &UTrapInteraction::CheckDiceValue, 0.8f,true);
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
							ADice* Dice = Cast<ADice>(PlayerDices[i]);
							FName face = Dice->FaceShowing;
							int* ptrVal = Dice->ValueMapping.Find(Dice->FaceShowing);
							int value;
							if (ptrVal) {
								 value = *ptrVal;
							}
							else {
								 value = 0;
							}
							if (value >= 5) {
								SkillTestPass = true;
								break;
							}
						}
					}
				}

				
				TArray<AActor*> DungeonDices;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), DungeonDiceClass, DungeonDices);
				if (DungeonDices.Num() != 0) {
					ADice* DDice = Cast<ADice>(DungeonDices[0]);
					if (DDice) {
						int value = *DDice->ValueMapping.Find(DDice->FaceShowing);
						UTrapReward* Widget = CreateWidget<UTrapReward>(UGameplayStatics::GetPlayerController(GetWorld(), 0), SecondWidgetClass);
						Widget->AddToViewport();
						Widget->ApplyAndShowReward(value, SkillTestPass);
					}
				}

			}//AQUI PETA, PERO NO HAY NADA XDDD
		}
	}
}
void UTrapInteraction::GetPlayerLevel(ABaseCharacter* Player)
{
	if (Player->Exp >= 18) {
		PlayerLevel = 3;
	}
	else if (Player->Exp >= 6) {
		PlayerLevel = 2;
	}
	else {
		PlayerLevel = 1;
	}
}
