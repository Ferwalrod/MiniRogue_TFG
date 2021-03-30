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

void APotionObject::UsePotion(ACharacter* User, ACharacter* Target)
{
	ABaseCharacter* Player = Cast<ABaseCharacter>(User);
	//Cast the target to monster. I can't cast because monster class is only in blueprint
	switch (Type) {
	case EPotionType::Fire_Potion:

		break;
	case EPotionType::Frost_Potion:

		break;
	case EPotionType::Health_Potion:

		break;
	case EPotionType::Holy_Water_Potion:

		break;
	case EPotionType::Perception_Potion:

		break;
	case EPotionType::Poison_Potion:

		break;
	}
}

TEnumAsByte<EPotionType> APotionObject::getType()
{
	return Type;
}

