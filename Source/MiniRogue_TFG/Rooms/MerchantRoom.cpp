// Fill out your copyright notice in the Description page of Project Settings.


#include "MerchantRoom.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "MiniRogue_TFG/MiniRogue_TFGGameModeBase.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "MiniRogue_TFG/MyGameInstance.h"
#include "MiniRogue_TFG/Rooms/BaseRoom.h"
#include "MiniRogue_TFG/Widgets/Merchant.h"
#include "Engine/World.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"

AMerchantRoom::AMerchantRoom() {

	PrimaryActorTick.bCanEverTick = true;
	RoomCollision->OnComponentBeginOverlap.AddDynamic(this, &AMerchantRoom::OnBeginOverlap);
}
void AMerchantRoom::BeginPlay()
{
	Super::ABaseRoom::BeginPlay();
}

void AMerchantRoom::Tick(float DeltaTime)
{
	Super::ABaseRoom::Tick(DeltaTime);
}

void AMerchantRoom::RoomBehavior()
{
    APlayerController* Controller =UGameplayStatics::GetPlayerController(GetWorld(), 0);
    Merchant_Widget=CreateWidget<UMerchant>(Controller, WidgetClass);
	Merchant_Widget->AddToViewport();

}

void AMerchantRoom::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor);
	if (Player) {
		Character = Player;
		RoomBehavior();
		GetWorldTimerManager().SetTimer(Timer, this, &AMerchantRoom::Check, 0.3f, true);
	}
}

void AMerchantRoom::Check()
{
	if (Merchant_Widget->CommerceFinished) {
		GetWorldTimerManager().ClearTimer(Timer);
		EventFinishRoom();
	}
}
