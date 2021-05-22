// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmoryRoom.h"
#include "Components/PrimitiveComponent.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "MiniRogue_TFG/Widgets/ArmoryThrowDice.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "MiniRogue_TFG/MiniRogue_TFGGameModeBase.h"

AArmoryRoom::AArmoryRoom() {
	PrimaryActorTick.bCanEverTick = true;

	RoomCollision->OnComponentBeginOverlap.AddDynamic(this, &AArmoryRoom::OnBeginOverlap);
	DiceRespawnPoint = CreateDefaultSubobject<USphereComponent>("Dice RespawnPoint");
	DiceRespawnPoint->SetupAttachment(GetRootComponent());
}

void AArmoryRoom::BeginPlay() {
	Super::BeginPlay();
}

void AArmoryRoom::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor);
	if (Player) {
		UArmoryThrowDice* Widget = CreateWidget<UArmoryThrowDice>(UGameplayStatics::GetPlayerController(GetWorld(), 0), WidgetClass);
		Widget->SetDiceRespawnPoint(DiceRespawnPoint);
		Widget->AddToViewport();
	}
}

void AArmoryRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AArmoryRoom::RoomBehavior()
{
}
