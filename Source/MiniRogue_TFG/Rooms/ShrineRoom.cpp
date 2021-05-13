// Fill out your copyright notice in the Description page of Project Settings.


#include "ShrineRoom.h"
#include "Components/SphereComponent.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "MiniRogue_TFG/Characters/RogueCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "MiniRogue_TFG/Widgets/ShrineInteraction1.h"


AShrineRoom::AShrineRoom() {

	PrimaryActorTick.bCanEverTick = true;
	DiceRespawnPoint = CreateDefaultSubobject<USphereComponent>("DiceRespawnPoint");
	DiceRespawnPoint->SetupAttachment(GetRootComponent());
	DiceRespawnPoint->OnComponentBeginOverlap.AddDynamic(this, &AShrineRoom::OnBeginOverlap);
}

void AShrineRoom::BeginPlay()
{
	Super::ABaseRoom::BeginPlay();
}

void AShrineRoom::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor);
	if (Player) {
		Character = Player;
		ARogueCharacter* Rogue = Cast<ARogueCharacter>(Player);
		if (Rogue && Rogue->EvasionActivated) {
			EventFinishRoom();
			Rogue->EvasionActivated = false;
		}
		else {
			UGameplayStatics::SetGamePaused(GetWorld(), true);
			UShrineInteraction1* Widget = CreateWidget<UShrineInteraction1>(UGameplayStatics::GetPlayerController(GetWorld(),0),WidgetClass);
			Widget->SetRespawnPoint(DiceRespawnPoint);
			Widget->AddToViewport();
		}
	}
}

void AShrineRoom::Tick(float DeltaTime)
{
	Super::ABaseRoom::Tick(DeltaTime);
}

void AShrineRoom::RoomBehavior()
{
}
