// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillFail.generated.h"

class ADice;
class UButton;
class UImage;
class ABaseCharacter;

UCLASS()
class MINIROGUE_TFG_API USkillFail : public UUserWidget
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int RewardChosen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		ABaseCharacter* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
		TSubclassOf<ADice> PlayerDiceClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
		TSubclassOf<ADice> DungeonDiceClass;
	//Widget Variables
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Accept;
	UPROPERTY(meta = (BindWidget))
		UImage* Fondo;

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime) override;

	//Macros
	void RemoveDices();
	//Functions
	UFUNCTION()
		void OnClicked_Accept();

};
