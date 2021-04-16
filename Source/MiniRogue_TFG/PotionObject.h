// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PotionObject.generated.h"

class ACharacter;

UCLASS(Abstract)
class MINIROGUE_TFG_API APotionObject : public AActor 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APotionObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void UsePotion(ACharacter* User, ACharacter* Target)PURE_VIRTUAL(APotionObject::UsePotion,);



};
