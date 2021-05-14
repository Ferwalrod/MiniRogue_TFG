// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniRogue_TFG/Rooms/BaseRoom.h"
#include "ShrineRoom.generated.h"

class USphereComponent;
class UShrineInteraction1;
class ADice;

UCLASS()
class MINIROGUE_TFG_API AShrineRoom : public ABaseRoom
{
	GENERATED_BODY()
	
public:
	AShrineRoom();

	//Components
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	USphereComponent* DiceRespawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice class")
	TSubclassOf<ADice> DiceClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice class")
	TSubclassOf<UShrineInteraction1> WidgetClass;
protected:
	virtual void BeginPlay() override;
public:

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult);

	virtual void Tick(float DeltaTime) override;
	virtual void RoomBehavior() override;

};
