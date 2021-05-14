// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShrineInteraction2.generated.h"

class ADice;
class USphereComponent;
class UImage;
class ABaseCharacter;
class UButton;
class UTextBlock;

UCLASS()
class MINIROGUE_TFG_API UShrineInteraction2 : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int Reward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		ABaseCharacter* PlayerCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		FString TXT_Reward_String;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int DiceResult;

	//Widget Components
	UPROPERTY(meta = (BindWidget))
		UButton* BTN_Accept;
	UPROPERTY(meta = (BindWidget))
		UImage* Fondo;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TXT_Reward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
		TSubclassOf<ADice> DungeonDiceClass;



	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime) override;


	UFUNCTION()
		void OnClicked_Button_Accept();

	//Events
	void Setup(int Result);
	//Macros
	void DestroyDices();
};
