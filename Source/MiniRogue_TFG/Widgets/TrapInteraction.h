// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "TrapInteraction.generated.h"

class ABaseCharacter;
class UButton;
class UImage;
class UTextBlock;
class UTexture2D;
class USphereComponent;
class ADice;
class AMiniRogue_TFGGameModeBase;
class UTrapReward;

UCLASS()
class MINIROGUE_TFG_API UTrapInteraction : public UUserWidget
{
	GENERATED_BODY()

private:
	FTimerHandle Timer;
	AMiniRogue_TFGGameModeBase* GM;
	int PlayerLevel=1;
public:
	//Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int RewardChosen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		ADice* PlayerDice;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		TSubclassOf<ADice> PlayerDiceClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		ADice* DungeonDice;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		TSubclassOf<ADice> DungeonDiceClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		bool SkillTestPass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int SkillTestValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		USphereComponent* DiceRespawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		TSubclassOf<UTrapReward> SecondWidgetClass;
	//Widget Variables
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Accept;
	UPROPERTY(meta = (BindWidget))
		UImage* Fondo;

	//Functions
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime) override;
	void GetPlayerLevel(ABaseCharacter* Player);
	
	void SetDiceRespawnPoint(USphereComponent* PointRef);

	//Macros
	void ThrowDices();
	//Events
	UFUNCTION()
		void OnClicked_Accept();


		void CheckDiceValue();
};
