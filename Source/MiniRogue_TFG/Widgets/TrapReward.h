// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TrapReward.generated.h"

class UTexture2D;
class UImage;
class UButton;
class UTextBlock;
class ABaseCharacter;

UCLASS()
class MINIROGUE_TFG_API UTrapReward : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icons")
		UTexture2D* IMG_Sword;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icons")
		UTexture2D* Armor_Ico;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icons")
		UTexture2D* Perception_potion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icons")
		UTexture2D* Holy_Potion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icons")
		UTexture2D* Health_ico;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icons")
		UTexture2D* Food_ico;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icons")
		UTexture2D* Poisoned_ico;
public:

	//Attributes
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
		int RewardIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
		int FloorIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
		ABaseCharacter* PlayerCharacter;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
		int PlayerHP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
		bool SkillTestPass;

	//Widgets Variables
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Accept;
	UPROPERTY(meta = (BindWidget))
		UImage* Fondo;
	UPROPERTY(meta = (BindWidget))
		UImage* IMG_Reward;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Text_Reward;

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime) override;

	//Functions
	void ApplyAndShowReward(int RewardIndexRes, bool SkillTestRes);

	void SetupWidget(FText TextReward, FString ImgReward);

	UFUNCTION()
		void OnClicked_Accept();
};
