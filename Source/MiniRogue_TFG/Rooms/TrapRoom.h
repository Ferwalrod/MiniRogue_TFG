// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniRogue_TFG/Rooms/BaseRoom.h"
#include "TrapRoom.generated.h"

class USphereComponent;
class UTrapInteraction;

UCLASS()
class MINIROGUE_TFG_API ATrapRoom : public ABaseRoom
{
	GENERATED_BODY()
	
public:
	ATrapRoom();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USphereComponent* DiceRespawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		TSubclassOf<UTrapInteraction> WidgetClass;



protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult);

	virtual void RoomBehavior() override;
};
