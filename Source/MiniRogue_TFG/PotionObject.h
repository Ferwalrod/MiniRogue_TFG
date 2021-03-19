// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enumerates/PotionType.h"
#include "Interfaces/Potion.h"
#include "PotionObject.generated.h"

UCLASS()
class MINIROGUE_TFG_API APotionObject : public AActor , public IPotion
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APotionObject();

	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EPotionType> Type;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UsePotion() override;
	TEnumAsByte<EPotionType> getType() override;


};
