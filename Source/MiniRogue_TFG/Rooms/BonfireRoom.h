// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniRogue_TFG/Rooms/BaseRoom.h"
#include "BonfireRoom.generated.h"

class UPrimitiveComponent;
class UBonfireInteraction;

UCLASS()
class MINIROGUE_TFG_API ABonfireRoom : public ABaseRoom
{
	GENERATED_BODY()
	
public:
	ABonfireRoom();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetClass")
		TSubclassOf<UBonfireInteraction> WidgetClass;

protected:
	virtual void BeginPlay() override;
public:

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult);

	virtual void Tick(float DeltaTime) override;
	virtual void RoomBehavior() override;
};
