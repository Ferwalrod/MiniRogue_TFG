// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"
#include "MiniRogue_TFGGameModeBase.h"
#include "Engine/World.h"
#include "MyGameInstance.h"

// Sets default values
ARoom::ARoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RoomCollision = CreateDefaultSubobject<UBoxComponent>("RoomCollision");
	SetRootComponent(RoomCollision);
	RoomCollision->OnComponentBeginOverlap.AddDynamic(this, &ARoom::OnBeginOverlap);

}

// Called when the game starts or when spawned
void ARoom::BeginPlay()
{
	Super::BeginPlay();
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
	if (GI) {
		IndexRoom = GI->RoomIndex;
	}
	
	
}

// Called every frame
void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ARoom::EventFinishRoom() {

	AMiniRogue_TFGGameModeBase* GM = Cast<AMiniRogue_TFGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GM) {
		GM->RoomFinished = true;

		switch (IndexRoom){
		case 0:

		break;
		case 2:

		break;
		
		case 3:

		break;
		default:
			break;
		}
	}

}
