// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"

#include "ShrineInteraction1.generated.h"

class ADice;
class USphereComponent;
class UImage;
class ABaseCharacter;
class UButton;

UCLASS()
class MINIROGUE_TFG_API UShrineInteraction1 : public UUserWidget
{
	GENERATED_BODY()
	
public:

	//Widget elements
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Fervorous_Pray;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Normal_Pray;
	UPROPERTY(meta = (BindWidget))
		UImage* Fondo;
	UPROPERTY(meta = (BindWidget))
		UImage* IMG_Shrine;

	//Attributes
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attributes")
		int Result;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		ADice* DungeonDice;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		ABaseCharacter* PlayerCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		TSubclassOf<ADice> DiceClass;

	USphereComponent* RespawnPoint;

	FTimerHandle Timer;

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime) override;
	//Events
	void SetRespawnPoint(USphereComponent* Point);
	void Check();
	UFUNCTION()
	void OnClicked_Normal_Pray();

	UFUNCTION()
	void OnClicked_Fervorous_Pray();

	//Macros
	void ThrowDice();

};
