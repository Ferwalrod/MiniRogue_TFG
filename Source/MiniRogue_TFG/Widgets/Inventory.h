// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MiniRogue_TFG/Enumerates/PotionType.h"
#include "Inventory.generated.h"

class ABaseCharacter;
class UProgressBar;
class UImage;
class UButton;
class UTextBlock;
class UVerticalBox;
class UCanvasPanel;

UCLASS()
class MINIROGUE_TFG_API UInventory : public UUserWidget
{
	GENERATED_BODY()
public:
	//Textures
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		UTexture2D* SwordIco;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		UTexture2D* AxeIco;
	//Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		TArray<FText> DescriptionTexts;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		FText DescriptionMessage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
		ABaseCharacter* PlayerCharacter;
	//Widget Variables
	UPROPERTY(meta = (BindWidget))
		UProgressBar* Armor_bar;
	UPROPERTY(meta = (BindWidget))
		UButton* Armor_button;
	UPROPERTY(meta = (BindWidget))
		UImage* BACKGROUND;
	UPROPERTY(meta = (BindWidget))
		UButton* Blinded_state;
	UPROPERTY(meta = (BindWidget))
		UButton* BTN_Close_Inventory;
	UPROPERTY(meta = (BindWidget))
		UButton* BTN_Weapon;
	UPROPERTY(meta = (BindWidget))
		UButton* Curse_State;
	UPROPERTY(meta = (BindWidget))
		UButton* exp_button;
	UPROPERTY(meta = (BindWidget))
		UProgressBar* Experience_bar;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Fire_potion_amount;
	UPROPERTY(meta = (BindWidget))
		UButton* Fire_potion_Button;
	UPROPERTY(meta = (BindWidget))
		UProgressBar* Food_bar;
	UPROPERTY(meta = (BindWidget))
		UButton* Food_Button;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Frost_potion_amount;
	UPROPERTY(meta = (BindWidget))
		UButton* Frost_potion_Button;
	UPROPERTY(meta = (BindWidget))
		UProgressBar* Gold_bar;
	UPROPERTY(meta = (BindWidget))
		UButton* Gold_button;
	UPROPERTY(meta = (BindWidget))
		UProgressBar* Health_bar;
	UPROPERTY(meta = (BindWidget))
		UButton* Health_button;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Health_potion_amount;
	UPROPERTY(meta = (BindWidget))
		UButton* Health_potion_Button;
	UPROPERTY(meta = (BindWidget))
		UButton* Holy_potion_Button;
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
		UImage* Image_102;
	UPROPERTY(meta = (BindWidget))
		UImage* Image_183;
	UPROPERTY(meta = (BindWidget))
		UImage* Image_256;
	UPROPERTY(meta = (BindWidget))
		UImage* Image_369;
	UPROPERTY(meta = (BindWidget))
		UImage* Image_421;
	UPROPERTY(meta = (BindWidget))
		UImage* image3;
	UPROPERTY(meta = (BindWidget))
		UImage* IMG_State_Blinded;
	UPROPERTY(meta = (BindWidget))
		UImage* IMG_State_Cursed;
	UPROPERTY(meta = (BindWidget))
		UImage* IMG_State_Perceptive;
	UPROPERTY(meta = (BindWidget))
		UImage* IMG_State_Poisoned;
	UPROPERTY(meta = (BindWidget))
		UImage* IMG_Weapon;
	UPROPERTY(meta = (BindWidget))
		UVerticalBox* Objects_section;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Perception_potion_amount;
	UPROPERTY(meta = (BindWidget))
		UButton* Perception_potion_Button;
	UPROPERTY(meta = (BindWidget))
		UButton* Perceptive_state;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Poison_potion_amount;
	UPROPERTY(meta = (BindWidget))
		UButton* Poison_potion_Button;
	UPROPERTY(meta = (BindWidget))
		UButton* Poisoned_state;
	UPROPERTY(meta = (BindWidget))
		UVerticalBox* Potions_section;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Sacred_potion_amount;
	UPROPERTY(meta = (BindWidget))
		UVerticalBox* Stats_box;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TXT_Armor_Value;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TXT_Exp_Value;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TXT_Food_Value;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TXT_Gold_Value;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TXT_Health_Value;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TXT_Weapon_Charges;
	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* Wrapper_Weapon;




	//Macros
	void UpdatePlayerStates();
	void UpdatePotions();
	void UpdateWeapons();
	//Functions
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime) override;

	void UpdateInterface();
	void SetPlayerCharacter(ABaseCharacter* Player);
	bool PlayerHasPotion(ABaseCharacter* Player,EPotionType PotionType);
	void UsePotionInventory(ABaseCharacter* Player, EPotionType PotionType);
	//On click events
	UFUNCTION()
		void OnClicked_Poison_potion_Button();
	UFUNCTION()
		void OnClicked_Fire_potion_Button();
	UFUNCTION()
		void OnClicked_Frost_potion_Button();
	UFUNCTION()
		void OnClicked_Health_potion_Button();
	UFUNCTION()
		void OnClicked_Holy_potion_Button();
	UFUNCTION()
		void OnClicked_Perception_potion_Button();
	UFUNCTION()
		void OnClicked_BTN_Close_Inventory();
	UFUNCTION()
		void OnClicked_BTN_Weapon();

	//On Hover /Unhover events
	UFUNCTION()
		void OnHovered_Exp_Button();
	UFUNCTION()
		void OnUnhovered_Exp_Button();
	UFUNCTION()
		void OnHovered_Health_Button();
	UFUNCTION()
		void OnUnhovered_Health_Button();
	UFUNCTION()
		void OnHovered_Food_Button();
	UFUNCTION()
		void OnUnhovered_Food_Button();
	UFUNCTION()
		void OnHovered_Armor_Button();
	UFUNCTION()
		void OnUnhovered_Armor_Button();
	UFUNCTION()
		void OnHovered_Gold_Button();
	UFUNCTION()
		void OnUnhovered_Gold_Button();
	UFUNCTION()
		void OnHovered_Curse_State();
	UFUNCTION()
		void OnUnhovered_Curse_State();
	UFUNCTION()
		void OnHovered_Poisoned_State();
	UFUNCTION()
		void OnUnhovered_Poisoned_State();
	UFUNCTION()
		void OnHovered_Blinded_State();
	UFUNCTION()
		void OnUnhovered_Blinded_State();
	UFUNCTION()
		void OnHovered_Poison_potion_Button();
	UFUNCTION()
		void OnUnhovered_Poison_potion_Button();
	UFUNCTION()
		void OnHovered_Fire_potion_Button();
	UFUNCTION()
		void OnUnhovered_Fire_potion_Button();
	UFUNCTION()
		void OnHovered_Frost_potion_Button();
	UFUNCTION()
		void OnUnhovered_Frost_potion_Button();
	UFUNCTION()
		void OnHovered_Health_potion_Button();
	UFUNCTION()
		void OnUnhovered_Health_potion_Button();
	UFUNCTION()
		void OnHovered_Holy_potion_Button();
	UFUNCTION()
		void OnUnhovered_Holy_potion_Button();
	UFUNCTION()
		void OnHovered_Perception_potion_Button();
	UFUNCTION()
		void OnUnhovered_Perception_potion_Button();
	UFUNCTION()
		void OnHovered_Perceptive_State();
	UFUNCTION()
		void OnUnhovered_Perceptive_State();
};
