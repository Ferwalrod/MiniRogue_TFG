// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniRogue_TFG/Rooms/BaseRoom.h"
#include "ArmoryRoom.generated.h"

class USphereComponent;
class UArmoryThrowDice;

UCLASS()
class MINIROGUE_TFG_API AArmoryRoom : public ABaseRoom
{
	GENERATED_BODY()
	
public:
	AArmoryRoom();
	//Attributes
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* DiceRespawnPoint;
	UPROPERTY(VisibleAnywhere, Category = "Widget")
		UArmoryThrowDice* WidgetRef;
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UArmoryThrowDice> WidgetClass;


protected:
	virtual void BeginPlay() override;
public:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult);

	virtual void Tick(float DeltaTime) override;
	virtual void RoomBehavior() override;
};
