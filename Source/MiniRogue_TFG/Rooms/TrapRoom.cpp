// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapRoom.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "MiniRogue_TFG/MiniRogue_TFGGameModeBase.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/Engine.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/TextRenderComponent.h"
#include "MiniRogue_TFG/MyGameInstance.h"
#include "MiniRogue_TFG/Widgets/TrapInteraction.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "MiniRogue_TFG/Characters/RogueCharacter.h"

ATrapRoom::ATrapRoom() {

	PrimaryActorTick.bCanEverTick = true;

	RoomCollision->OnComponentBeginOverlap.AddDynamic(this, &ATrapRoom::OnBeginOverlap);
	DiceRespawnPoint = CreateDefaultSubobject<USphereComponent>("Dice Respawn Point");
	DiceRespawnPoint->SetupAttachment(GetRootComponent());
}

void ATrapRoom::BeginPlay()
{
	Super::ABaseRoom::BeginPlay();
}

void ATrapRoom::Tick(float DeltaTime)
{
	Super::ABaseRoom::Tick(DeltaTime);
}

void ATrapRoom::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor);
	if (Player) {
		Character = Player;
		Character->RightArrowVisibility = false;
		Character->BottomArrowVisibility = false;
		ARogueCharacter* Rogue = Cast<ARogueCharacter>(Character);
		if (Rogue && Rogue->EvasionActivated) {
			EventFinishRoom();
			Rogue->EvasionActivated = false;
		}
		else {
			UTrapInteraction* Widget = CreateWidget<UTrapInteraction>(UGameplayStatics::GetPlayerController(GetWorld(),0),WidgetClass);
			Widget->SetDiceRespawnPoint(DiceRespawnPoint);
			Widget->AddToViewport();
		}
	}
}

void ATrapRoom::RoomBehavior()
{
}
