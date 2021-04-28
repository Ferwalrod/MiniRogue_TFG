// Fill out your copyright notice in the Description page of Project Settings.


#include "AberrationRoom.h"


AAberrationRoom::AAberrationRoom() {
	PrimaryActorTick.bCanEverTick = true;
}
void AAberrationRoom::BeginPlay()
{
	Super::BeginPlay();
}

void AAberrationRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
