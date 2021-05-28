// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Merchant.generated.h"

class APotionObject;
class ABaseCharacter;
class UButton;
class UTextBlock;
class UImage;

UCLASS()
class MINIROGUE_TFG_API UMerchant : public UUserWidget
{
	GENERATED_BODY()

public:
	//Widget Elements
	
	UPROPERTY(meta = (BindWidget))
	UButton* Buy_Fire_potion_Button;
	UPROPERTY(meta = (BindWidget))
		UButton* Sell_Fire_potion_Button;
	UPROPERTY(meta = (BindWidget))
	UButton* Buy_Frost_potion_Button;
	UPROPERTY(meta = (BindWidget))
		UButton* Sell_Frost_potion_Button;
	UPROPERTY(meta = (BindWidget))
	UButton* Buy_Health_potion_Button;
	UPROPERTY(meta = (BindWidget))
		UButton* Sell_Health_potion_Button;
	UPROPERTY(meta = (BindWidget))
	UButton* Buy_Holy_potion_Button;
	UPROPERTY(meta = (BindWidget))
		UButton* Sell_Holy_potion_Button;
	UPROPERTY(meta = (BindWidget))
	UButton* Buy_Perception_potion_Button;
	UPROPERTY(meta = (BindWidget))
		UButton* Sell_Perception_potion_Button;
	UPROPERTY(meta = (BindWidget))
	UButton* Buy_Poison_potion_Button;
	UPROPERTY(meta = (BindWidget))
		UButton* Sell_Poison_potion_Button;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Fire_potion_amount;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Frost_potion_amount;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Health_potion_amount;
	UPROPERTY(meta = (BindWidget))
		UImage* Image;
	UPROPERTY(meta = (BindWidget))
		UImage* Image_1;
	UPROPERTY(meta = (BindWidget))
		UImage* Image_2;
	UPROPERTY(meta = (BindWidget))
		UImage* Image_3;
	UPROPERTY(meta = (BindWidget))
		UImage* Image_4;
	UPROPERTY(meta = (BindWidget))
		UImage* Image_172;
	UPROPERTY(meta = (BindWidget))
		UImage* Image_252;
	UPROPERTY(meta = (BindWidget))
		UImage* Image_302;
	UPROPERTY(meta = (BindWidget))
		UImage* Image_349;
	UPROPERTY(meta = (BindWidget))
		UImage* Image_408;
	UPROPERTY(meta = (BindWidget))
		UImage* Image_505;
	UPROPERTY(meta = (BindWidget))
		UImage* Image_644;
	UPROPERTY(meta = (BindWidget))
		UImage* image3;
	UPROPERTY(meta = (BindWidget))
		UButton* Leave_Button;
	UPROPERTY(meta = (BindWidget))
		UButton* Option1;
	UPROPERTY(meta = (BindWidget))
		UButton* Option2;
	UPROPERTY(meta = (BindWidget))
		UButton* Option3;
	UPROPERTY(meta = (BindWidget))
		UButton* Option4;
	UPROPERTY(meta = (BindWidget))
		UButton* Option5;
	UPROPERTY(meta = (BindWidget))
		UButton* Option6No_Function;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Perception_potion_amount;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Poison_potion_amount;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Sacred_potion_amount;
	UPROPERTY(meta = (BindWidget))
		UButton* Sell_Option1;
	UPROPERTY(meta = (BindWidget))
		UButton* Sell_Option2No_Function;

	//Attributes

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		TArray<FText> DescriptionTexts;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FText DescriptionText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	ABaseCharacter* Player;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FText GoldAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FText ArmorAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FText FoodAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	bool CommerceFinished;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	bool HasPotion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	TSubclassOf<APotionObject> PotionsToTrade;


	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime) override;

	//Macros
	void RefreshGold(int Gold);
	void RefreshFood(int Food);
	void RefreshArmor(int Armor);
	void RefreshPotions();

	//Button & hover functions

	UFUNCTION()
		void OnClicked_Sell_Option1();
	UFUNCTION()
		void OnClicked_Leave_Button();

	//Buy Elements logic of the card
	UFUNCTION()
		void OnClicked_Option1();
	UFUNCTION()
		void OnClicked_Option2();
	UFUNCTION()
		void OnClicked_Option3();
	UFUNCTION()
		void OnClicked_Option4();
	UFUNCTION()
		void OnClicked_Option5();

	//Buy Potions logic

	UFUNCTION()
		void OnClicked_Buy_Fire_potion_Button();
	UFUNCTION()
		void OnClicked_Buy_Frost_potion_Button();
	UFUNCTION()
		void OnClicked_Buy_Holy_potion_Button();
	UFUNCTION()
		void OnClicked_Buy_Health_potion_Button();
	UFUNCTION()
		void OnClicked_Buy_Perception_potion_Button();
	UFUNCTION()
		void OnClicked_Buy_Poison_potion_Button();

	//Sell Potions logic

	UFUNCTION()
		void OnClicked_Sell_Fire_potion_Button();
	UFUNCTION()
		void OnClicked_Sell_Frost_potion_Button();
	UFUNCTION()
		void OnClicked_Sell_Holy_potion_Button();
	UFUNCTION()
		void OnClicked_Sell_Health_potion_Button();
	UFUNCTION()
		void OnClicked_Sell_Perception_potion_Button();
	UFUNCTION()
		void OnClicked_Sell_Poison_potion_Button();

	// Un/hover over the buy elements of the card

	UFUNCTION()
		void OnHovered_Option1();
	UFUNCTION()
		void OnUnhovered_Option1();
	UFUNCTION()
		void OnHovered_Option2();
	UFUNCTION()
		void OnUnhovered_Option2();
	UFUNCTION()
		void OnHovered_Option3();
	UFUNCTION()
		void OnUnhovered_Option3();
	UFUNCTION()
		void OnHovered_Option4();
	UFUNCTION()
		void OnUnhovered_Option4();
	UFUNCTION()
		void OnHovered_Option5();
	UFUNCTION()
		void OnUnhovered_Option5();

	//Un/hover over the sell elements of the  card

	UFUNCTION()
		void OnHovered_Sell_Option1();
	UFUNCTION()
		void OnUnhovered_Sell_Option1();

	//Un/hover over the buy potions

	UFUNCTION()
		void OnHovered_Buy_Fire_potion_Button();
	UFUNCTION()
		void OnUnhovered_Buy_Fire_potion_Button();
	UFUNCTION()
		void OnHovered_Buy_Frost_potion_Button();
	UFUNCTION()
		void OnUnhovered_Buy_Frost_potion_Button();
	UFUNCTION()
		void OnHovered_Buy_Health_potion_Button();
	UFUNCTION()
		void OnUnhovered_Buy_Health_potion_Button();
	UFUNCTION()
		void OnHovered_Buy_Holy_potion_Button();
	UFUNCTION()
		void OnUnhovered_Buy_Holy_potion_Button();
	UFUNCTION()
		void OnHovered_Buy_Perception_potion_Button();
	UFUNCTION()
		void OnUnhovered_Buy_Perception_potion_Button();
	UFUNCTION()
		void OnHovered_Buy_Poison_potion_Button();
	UFUNCTION()
		void OnUnhovered_Buy_Poison_potion_Button();

	//Un/hover over the sell potions

	UFUNCTION()
		void OnHovered_Sell_Fire_potion_Button();
	UFUNCTION()
		void OnUnhovered_Sell_Fire_potion_Button();
	UFUNCTION()
		void OnHovered_Sell_Frost_potion_Button();
	UFUNCTION()
		void OnUnhovered_Sell_Frost_potion_Button();
	UFUNCTION()
		void OnHovered_Sell_Health_potion_Button();
	UFUNCTION()
		void OnUnhovered_Sell_Health_potion_Button();
	UFUNCTION()
		void OnHovered_Sell_Holy_potion_Button();
	UFUNCTION()
		void OnUnhovered_Sell_Holy_potion_Button();
	UFUNCTION()
		void OnHovered_Sell_Perception_potion_Button();
	UFUNCTION()
		void OnUnhovered_Sell_Perception_potion_Button();
	UFUNCTION()
		void OnHovered_Sell_Poison_potion_Button();
	UFUNCTION()
		void OnUnhovered_Sell_Poison_potion_Button();

};
