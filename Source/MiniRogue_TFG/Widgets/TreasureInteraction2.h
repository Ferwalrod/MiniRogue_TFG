// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MiniRogue_TFG/Structs/RewardOption.h"
#include "TreasureInteraction2.generated.h"

class ABaseCharacter;
class UButton;
class UImage;
class UTextBlock;
class UTreasureInteraction2;
class UTexture2D;


UCLASS()
class MINIROGUE_TFG_API UTreasureInteraction2 : public UUserWidget
{
	GENERATED_BODY()

public:

	//Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attrbutes")
		int RewardChosen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attrbutes")
		TArray<FRewardOption> Rewards;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attrbutes")
		FString LeftReward;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attrbutes")
		FString RightReward;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attrbutes")
		FRewardOption Reward;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attrbutes")
		bool Reward1Selected;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attrbutes")
		FRewardOption RewardChoose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attrbutes")
		UTexture2D* ArmorIco;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attrbutes")
		UTexture2D* ExpIco;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attrbutes")
		UTexture2D* GoldIco;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attrbutes")
		UTexture2D* PerceptionIco;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attrbutes")
		UTexture2D* FrostIco;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attrbutes")
		UTexture2D* FireIco;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attrbutes")
		UTexture2D* PoisonIco;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attrbutes")
		UTexture2D* RefreshIco;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attrbutes")
		UTexture2D* HealthIco;

	//Widget Variables
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Accept;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Reward_Left;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Reward_Right;
	UPROPERTY(meta = (BindWidget))
		UImage* Fondo;
	UPROPERTY(meta = (BindWidget))
		UImage* Img_left_border_seleccted;
	UPROPERTY(meta = (BindWidget))
		UImage* IMG_Reward_Left;
	UPROPERTY(meta = (BindWidget))
		UImage* IMG_Reward_Right;
	UPROPERTY(meta = (BindWidget))
		UImage* Img_right_border_seleccted;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Text_Reward1;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Text_Reward2;

	//Functions
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime) override;
	FRewardOption GetRandomReward();
	void ChangeImage(FText Text,UImage* Image);
	void ApplyReward(ABaseCharacter* Player,FText Reward);

	UFUNCTION()
		void OnClicked_Accept();
	UFUNCTION()
		void OnClicked_Reward_Left();
	UFUNCTION()
		void OnClicked_Reward_Right();
	
};
