// Fill out your copyright notice in the Description page of Project Settings.


#include "TreasureRoom.h"
#include "Components/BoxComponent.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "MiniRogue_TFG/Characters/RogueCharacter.h"
#include "MiniRogue_TFG/MyGameInstance.h"
//#include "MiniRogue_TFG/Rooms/TrapRoom.h"
#include "MiniRogue_TFG/Rooms/MonsterRoom.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "MiniRogue_TFG/Widgets/TreasureInteraction1.h"

ATreasureRoom::ATreasureRoom() {

	PrimaryActorTick.bCanEverTick = true;
	RoomCollision->OnComponentBeginOverlap.AddDynamic(this, &ATreasureRoom::OnBeginOverlap);
}

void ATreasureRoom::BeginPlay()
{
	Super::ABaseRoom::BeginPlay();
}

void ATreasureRoom::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor);
	if (Character) {
		PlayerCharacter = Character;
		GiveGoldReward();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		UTreasureInteraction1* Widget = CreateWidget<UTreasureInteraction1>(Controller, WidgetClass);
		Widget->AddToViewport();
	}
}

void ATreasureRoom::Tick(float DeltaTime)
{
	Super::ABaseRoom::Tick(DeltaTime);
}

void ATreasureRoom::RoomBehavior()
{
}

void ATreasureRoom::GiveGoldReward()
{
	if (GI) {
		if (GI->VisitedRooms.Num() > 1) {

		}
		else {
			PlayerCharacter->Gold = UKismetMathLibrary::Clamp(PlayerCharacter->Gold+GoldReceived,0,PlayerCharacter->MaxGold);
		}

	}
}
