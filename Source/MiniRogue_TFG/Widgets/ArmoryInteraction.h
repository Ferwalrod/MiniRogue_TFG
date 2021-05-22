// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArmoryInteraction.generated.h"

class ADice;
class ABaseCharacter;
class UButton;
class UTextBlock;
class UImage;

UCLASS()
class MINIROGUE_TFG_API UArmoryInteraction : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//Textures
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Textures")
		UTexture2D* SwordIco;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Textures")
		UTexture2D* AxeIco;

	//Attributes & Classes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		ABaseCharacter* Player;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		FString TXT_Reward_String;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
		TSubclassOf<ADice> PlayerDiceClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
		TSubclassOf<ADice> DungeonDiceClass;
	//Widget Variables
	UPROPERTY(meta = (BindWidget))
		UButton* BTN_Accept;
	UPROPERTY(meta = (BindWidget))
		UImage* Fondo;
	UPROPERTY(meta = (BindWidget))
		UImage* IMG_Weapon;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TXT_Reward;

	void Setup(int NumReward);
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime) override;
	UFUNCTION()
		void OnClicked_Button_Accept();
	//Macros
	void RemoveDices();

};
