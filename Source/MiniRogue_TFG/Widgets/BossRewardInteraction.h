// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MiniRogue_TFG/Structs/RewardOption.h"
#include "BossRewardInteraction.generated.h"


class UButton;
class UTextBlock;
class UImage;
class ABaseCharacter;
class ABossRoom;

UCLASS()
class MINIROGUE_TFG_API UBossRewardInteraction : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//Attributes
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
		int RewardChosen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		TArray<FRewardOption> Rewards;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
		FString LeftReward;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
		FString RightReward;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
		FRewardOption Reward;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
		bool Reward1Selected;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
		FRewardOption RewardChoose;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
		ABossRoom* BossRoomRef;

	//Textures
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
		UTexture2D* HolyIco;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attrbutes")
		UTexture2D* HealthIco;

	//WidgetVariables
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
	FRewardOption getRandomReward();
	void ChangeImage(FText Text, UImage* Image);
	void ApplyReward(ABaseCharacter* Player,FText Text);

	UFUNCTION()
		void OnClicked_Accept_Button();
	UFUNCTION()
		void OnClicked_Left_Reward_Button();
	UFUNCTION()
		void OnClicked_Right_Reward_Button();
};
