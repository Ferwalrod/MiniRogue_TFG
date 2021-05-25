// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniRogue_TFG/Rooms/BaseRoom.h"
#include "TreasureRoom.generated.h"

class ABaseCharacter;
class UTreasureInteraction1;

UCLASS()
class MINIROGUE_TFG_API ATreasureRoom : public ABaseRoom
{
	GENERATED_BODY()

public:
	ATreasureRoom();
	//Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		ABaseCharacter* PlayerCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int GoldReceived=1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		TSubclassOf<UTreasureInteraction1> WidgetClass;
protected:
	virtual void BeginPlay() override;
public:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult);

	virtual void Tick(float DeltaTime) override;
	virtual void RoomBehavior() override;

	//Macros
	void GiveGoldReward();
	
};
