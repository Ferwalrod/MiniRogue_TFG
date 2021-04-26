// Fill out your copyright notice in the Description page of Project Settings.


#include "GoblinRoom.h"

AGoblinRoom::AGoblinRoom() {
	PrimaryActorTick.bCanEverTick = true;
}
void AGoblinRoom::BeginPlay()
{
	Super::AMonsterRoom::BeginPlay();
}

void AGoblinRoom::Tick(float DeltaTime)
{
	Super::AMonsterRoom::Tick(DeltaTime);
}
