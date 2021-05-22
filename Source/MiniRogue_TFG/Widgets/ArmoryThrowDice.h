// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "ArmoryThrowDice.generated.h"


class USphereComponent;
class ADice;
class UArmoryInteraction;
class USkillFail;
class UButton;
class UImage;

UCLASS()
class MINIROGUE_TFG_API UArmoryThrowDice : public UUserWidget
{
	GENERATED_BODY()
	
private:
	FTimerHandle Timer;
	AMiniRogue_TFGGameModeBase* GM;
	int PlayerLevel = 1;
public:
	//Atributes
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
		int RewardChosen;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
		ADice* PlayerDice;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
		ADice* DungeonDice;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
		bool SkillTestPass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
		int SkillTestValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USphereComponent* DiceRespawnPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
		TSubclassOf<ADice> PlayerDiceClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
		TSubclassOf<ADice> DungeonDiceClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
		TSubclassOf<UArmoryInteraction> SuccessWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
		TSubclassOf<USkillFail> FailWidgetClass;

	//Widget Variables
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Accept;
	UPROPERTY(meta = (BindWidget))
		UImage* Fondo;

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime) override;

	void GetPlayerLevel(ABaseCharacter* Player);
	void SetDiceRespawnPoint(USphereComponent* Point);

	//Events
	void CheckDiceValue();
	UFUNCTION()
		void OnClicked_Button_Accept();
	//Macros
	void ThrowDices();
};
