// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BonfireInteraction.generated.h"

class APotionObject;
class ABaseCharacter;
class UButton;
class UTextBlock;
class UImage;

UCLASS()
class MINIROGUE_TFG_API UBonfireInteraction : public UUserWidget
{
	GENERATED_BODY()

public:
	//Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int RewardChosen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	ABaseCharacter* PlayerCharacter;

	//Widget elements
	UPROPERTY(meta = (BindWidget))
		UImage* Border_Exp;
	UPROPERTY(meta = (BindWidget))
		UImage* Border_Food;
	UPROPERTY(meta = (BindWidget))
		UImage* Border_Hp;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Accept;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Exp;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Food;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Hp;
	UPROPERTY(meta = (BindWidget))
		UImage* Fondo;
	UPROPERTY(meta = (BindWidget))
		UImage* IMG_Bonfire;
	UPROPERTY(meta = (BindWidget))
		UImage* IMG_Food;
	UPROPERTY(meta = (BindWidget))
		UImage* IMG_Hp;


public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime) override;

	void ShowFocusedBorder(UImage* Border);

	UFUNCTION()
		void OnClicked_Button_Food();
	UFUNCTION()
		void OnClicked_Button_Exp();
	UFUNCTION()
		void OnClicked_Button_Hp();
	UFUNCTION()
		void OnClicked_Accept();

};
