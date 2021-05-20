// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserInterface.generated.h"


class UTextBlock;
class UImage;
class UButton;
class UProgressBar;
class UInvalidationBox;
class UVerticalBox;
class UInventory;
class ABaseCharacter;
class UPause;
class UTexture2D;

UCLASS()
class MINIROGUE_TFG_API UUserInterface : public UUserWidget
{
	GENERATED_BODY()

public:
	//Widget Variables
	UPROPERTY(meta = (BindWidget))
		UImage* background_counter_txt;
	UPROPERTY(meta = (BindWidget))
		UButton* BTN_Map_and_Progress;
	UPROPERTY(meta = (BindWidget))
		UButton* BTN_Skill_1;
	UPROPERTY(meta = (BindWidget))
		UButton* BTN_Skill_2;
	UPROPERTY(meta = (BindWidget))
		UButton* BTN_Weapon;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_crow;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Pause;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Crow_text;
	UPROPERTY(meta = (BindWidget))
		UProgressBar* Exp_Bar;
	UPROPERTY(meta = (BindWidget))
		UProgressBar* Health_Bar;
	UPROPERTY(meta = (BindWidget))
		UButton* Ico_Character;
	UPROPERTY(meta = (BindWidget))
		UImage* Image_113;
	UPROPERTY(meta = (BindWidget))
		UImage* Image_116;
	UPROPERTY(meta = (BindWidget))
		UImage* Image_753;
	UPROPERTY(meta = (BindWidget))
		UImage* IMG_Armor;
	UPROPERTY(meta = (BindWidget))
		UImage* IMG_Food;
	UPROPERTY(meta = (BindWidget))
		UImage* IMG_Gold;
	UPROPERTY(meta = (BindWidget))
		UImage* IMG_Map;
	UPROPERTY(meta = (BindWidget))
		UImage* IMG_Skill_1;
	UPROPERTY(meta = (BindWidget))
		UImage* IMG_Skill_2;
	UPROPERTY(meta = (BindWidget))
		UImage* IMG_Weapon;
	UPROPERTY(meta = (BindWidget))
		UInvalidationBox* InvalidationBox_Character_Avatar;
	UPROPERTY(meta = (BindWidget))
		UInvalidationBox* InvalidationBox_Map;
	UPROPERTY(meta = (BindWidget))
		UInvalidationBox* InvalidationBox_Skills;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TXT_Armor_Count;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TXT_Exp_Count;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TXT_Food_Count;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TXT_Gold_Count;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TXT_Weapon_Charges;
	UPROPERTY(meta = (BindWidget))
		UVerticalBox* VBOX_Weapon;

	//Attributes
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Attributes")
	ABaseCharacter* PlayerCharacter;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget References")
		UInventory* UMG_Inventory_Ref;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget References")
		UPause* UMG_Pause_Ref;

	//Widget classes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget classes")
		TSubclassOf<UPause> PauseWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget classes")
		TSubclassOf<UInventory> InventoryWidgetClass;
	/*
	 Map reference here
	*/
	//Texture2D
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Textures")
		UTexture2D* SwordTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Textures")
		UTexture2D* AxeTexture;
	//Functions
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime) override;
	void SetPlayerCharacter(ABaseCharacter* Player);
	bool IsPlayerInCombat();
	float GetExpBarPercent();
	float GetHealthBarPercent();

	//Events
	void UpdateInterface();
	void ShowSkillsButtons();
	void HideSkillsButtons();
	UFUNCTION()
		void OnClicked_Button_Pause();
	UFUNCTION()
		void OnClicked_BTN_Skill_1();
	UFUNCTION()
		void OnClicked_BTN_Skill_2();
	UFUNCTION()
		void OnClicked_BTN_Map_And_Progress();
	UFUNCTION()
		void OnClicked_Ico_Character();
	UFUNCTION()
		void OnClicked_BTN_Weapon();


};
