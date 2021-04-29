// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniRogue_TFG/Rooms/BaseRoom.h"
#include "MerchantRoom.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class AMiniRogue_TFGGameModeBase;
class APlayerController;
class AActor;
class UPrimitiveComponent;
class UBoxComponent;
class UUserWidget;
class UMerchant;

UCLASS()
class MINIROGUE_TFG_API AMerchantRoom : public ABaseRoom
{
	GENERATED_BODY()

public:
	AMerchantRoom();
	//Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	UMerchant* Merchant_Widget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget Class")
	TSubclassOf<UMerchant> WidgetClass;

	FTimerHandle Timer;
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void RoomBehavior() override;

	//Functions
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult);
	
	//Events
	void Check();
};
