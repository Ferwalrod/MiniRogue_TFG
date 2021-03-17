// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "Characters/BaseCharacter.h"
#include "Components/BoxComponent.h"
#include "MyGameInstance.h"
#include "GameFramework/Actor.h"
#include "Room.generated.h"

UCLASS()
class MINIROGUE_TFG_API ARoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoom();

	//Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Attributes")
	int IndexRoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Attributes")
	ABaseCharacter* Player;

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* RoomCollision;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult);

	void EventFinishRoom();

};
