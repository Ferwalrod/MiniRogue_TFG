// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseRoom.generated.h"

class ABaseCharacter;
class UBoxComponent;
class AActor;
class UPrimitiveComponent;

UCLASS(Abstract)
class MINIROGUE_TFG_API ABaseRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseRoom();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Attributes")
	int IndexRoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Attributes")
	ABaseCharacter* Character;

	//Components
	//Room collision is the box which triggers the room
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* RoomCollision;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void RoomBehavior()PURE_VIRTUAL(ABaseRoom::RoomBehavior, );

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void EventFinishRoom();
	
	

};
