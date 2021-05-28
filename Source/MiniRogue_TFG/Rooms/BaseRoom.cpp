// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseRoom.h"
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


// Sets default values
ABaseRoom::ABaseRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RoomCollision = CreateDefaultSubobject<UBoxComponent>("RoomCollision");
	SetRootComponent(RoomCollision);
	Scenery1 = CreateDefaultSubobject<UStaticMeshComponent>("Scenery1");
	Scenery1->SetupAttachment(GetRootComponent());
	Scenery2 = CreateDefaultSubobject<UStaticMeshComponent>("Scenery2");
	Scenery2->SetupAttachment(GetRootComponent());
	Scenery3 = CreateDefaultSubobject<UStaticMeshComponent>("Scenery3");
	Scenery3->SetupAttachment(GetRootComponent());
	Scenery4 = CreateDefaultSubobject<UStaticMeshComponent>("Scenery4");
	Scenery4->SetupAttachment(GetRootComponent());
	Scenery5 = CreateDefaultSubobject<UStaticMeshComponent>("Scenery5");
	Scenery5->SetupAttachment(GetRootComponent());
	Scenery6 = CreateDefaultSubobject<UStaticMeshComponent>("Scenery6");
	Scenery6->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ABaseRoom::BeginPlay()
{
	Super::BeginPlay();

	GI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	if (GI) {
		IndexRoom = GI->RoomIndex;
		FString Name;
	}
	
}

// Called every frame
void ABaseRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABaseRoom::EventFinishRoom()
{
	AMiniRogue_TFGGameModeBase* GM = Cast<AMiniRogue_TFGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GM) {
		GM->RoomFinished = true;
		switch (IndexRoom) {
		case 0:
			Character->BottomArrowVisibility = true;
			Character->RightArrowVisibility = true;
			break;
		case 1:
			Character->BottomArrowVisibility = true;
			Character->RightArrowVisibility = true;
			break;
		case 2:
			Character->BottomArrowVisibility = true;
			break;
		case 3:
			Character->BottomArrowVisibility = true;
			Character->RightArrowVisibility = true;
			break;
		case 4:
			Character->BottomArrowVisibility = true;
			Character->RightArrowVisibility = true;
			break;
		case 5:
			Character->BottomArrowVisibility = true;
			break;
		case 6:
			Character->RightArrowVisibility = true;
			break;
		case 7:
			Character->RightArrowVisibility = true;
			break;
		}
	}
}

