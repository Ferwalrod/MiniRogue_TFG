// Fill out your copyright notice in the Description page of Project Settings.


#include "UndeadRoom.h"

AUndeadRoom::AUndeadRoom() {
	PrimaryActorTick.bCanEverTick = true;
}
void AUndeadRoom::BeginPlay()
{
	Super::BeginPlay();
}

void AUndeadRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
