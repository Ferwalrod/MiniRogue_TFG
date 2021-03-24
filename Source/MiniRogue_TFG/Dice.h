// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "DiceType.h"
#include "GameFramework/Actor.h"
#include "Dice.generated.h"

UCLASS()
class MINIROGUE_TFG_API ADice : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADice();

	//Attributes
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Attributes")
	TMap<FName, int> ValueMapping;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	FName FaceShowing;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	float Hightest;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	TEnumAsByte<EDiceType> Type;

	//Components
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	UStaticMeshComponent* Dice;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnSleep(UPrimitiveComponent* sleeper,FName Bone);


};
