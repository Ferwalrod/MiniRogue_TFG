// Fill out your copyright notice in the Description page of Project Settings.


#include "BonfireRoom.h"
#include "Components/PrimitiveComponent.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "Components/BoxComponent.h"
#include "MiniRogue_TFG/MyGameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "MiniRogue_TFG/MiniRogue_TFGGameModeBase.h"
#include "MiniRogue_TFG/Widgets/BonfireInteraction.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

ABonfireRoom::ABonfireRoom() {
	PrimaryActorTick.bCanEverTick = true;
	RoomCollision->OnComponentBeginOverlap.AddDynamic(this, &ABonfireRoom::OnBeginOverlap);
	
}
void ABonfireRoom::BeginPlay()
{
	Super::ABaseRoom::BeginPlay();
}
void ABonfireRoom::Tick(float DeltaTime)
{
	Super::ABaseRoom::Tick(DeltaTime);
}

void ABonfireRoom::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor);
	if (Player) {
		Character = Player;
		RoomBehavior();
	}
}

void ABonfireRoom::RoomBehavior()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (Controller) {
		UBonfireInteraction* Widget = CreateWidget<UBonfireInteraction>(Controller, WidgetClass);
		Widget->AddToViewport();
		FInputModeUIOnly UI;
		UI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		Controller->SetInputMode(UI);
		Controller->bShowMouseCursor = true;
		UGameplayStatics::SetGamePaused(GetWorld(),true);
	}
}
