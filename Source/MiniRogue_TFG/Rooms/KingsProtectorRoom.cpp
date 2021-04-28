// Fill out your copyright notice in the Description page of Project Settings.


#include "KingsProtectorRoom.h"


AKingsProtectorRoom::AKingsProtectorRoom() {
	PrimaryActorTick.bCanEverTick = true;
}
void AKingsProtectorRoom::BeginPlay()
{
	Super::BeginPlay();
}

void AKingsProtectorRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
