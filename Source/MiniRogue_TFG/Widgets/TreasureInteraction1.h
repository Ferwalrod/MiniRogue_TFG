// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TreasureInteraction1.generated.h"

class ABaseCharacter;
class UButton;
class UImage;
class UTreasureInteraction2;

UCLASS()
class MINIROGUE_TFG_API UTreasureInteraction1 : public UUserWidget
{
	GENERATED_BODY()
	

public:
	//Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attrbutes")
		int RewardChosen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attrbutes")
		TSubclassOf<UTreasureInteraction2> SecondWidgetClass;

	//Widget variables

	UPROPERTY(meta = (BindWidget))
		UButton* Button_Accept;
	UPROPERTY(meta = (BindWidget))
		UImage* Fondo;


	//Functions
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime) override;

	UFUNCTION()
		void OnClicked_Accept();

};
