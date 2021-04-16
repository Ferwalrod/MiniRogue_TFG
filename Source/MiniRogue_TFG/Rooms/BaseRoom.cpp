// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseRoom.h"
#include "Components/PrimitiveComponent.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "Components/BoxComponent.h"
#include "MiniRogue_TFG/MyGameInstance.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "MiniRogue_TFG/MiniRogue_TFGGameModeBase.h"


// Sets default values
ABaseRoom::ABaseRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RoomCollision = CreateDefaultSubobject<UBoxComponent>("RoomCollision");
	RoomCollision->AttachTo(GetRootComponent());
	RoomCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseRoom::OnBeginOverlap);

}

// Called when the game starts or when spawned
void ABaseRoom::BeginPlay()
{
	Super::BeginPlay();

	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
	if (GI) {
		IndexRoom = GI->RoomIndex;
	}
	
}

// Called every frame
void ABaseRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseRoom::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* BC = Cast<ABaseCharacter>(OtherActor);
	if (BC) {
		Character = BC;
		RoomBehavior();
	}
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

