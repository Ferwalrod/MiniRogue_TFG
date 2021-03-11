// Fill out your copyright notice in the Description page of Project Settings.


#include "Dice.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "MiniRogue_TFG/MiniRogue_TFGGameModeBase.h"

// Sets default values
ADice::ADice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Dice = CreateDefaultSubobject<UStaticMeshComponent>("Dice");
	SetRootComponent(Dice);
	Dice->OnComponentSleep.AddDynamic(this,&ADice::OnSleep);
	Dice->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ADice::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADice::OnSleep(UPrimitiveComponent* sleeper, FName Bone)
{
	Hightest = -9999.f;
	TArray<FName> sockets = Dice->GetAllSocketNames();
	for (FName socket : sockets) {
		float Z= Dice->GetSocketLocation(socket).Z;
		if (Z > Hightest) {
			Hightest = Z;
			FaceShowing = socket;
		}
	}
	AMiniRogue_TFGGameModeBase* GM = Cast<AMiniRogue_TFGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GM) {
		GM->Results.Add(Type, ValueMapping[FaceShowing]);
	}
}

