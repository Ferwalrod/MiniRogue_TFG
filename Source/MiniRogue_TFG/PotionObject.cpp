// Fill out your copyright notice in the Description page of Project Settings.


#include "PotionObject.h"

// Sets default values
APotionObject::APotionObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APotionObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APotionObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APotionObject::UsePotion()
{
}

TEnumAsByte<EPotionType> APotionObject::getType()
{
	return Type;
}
