// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Merchant.generated.h"

class APotionObject;
class ABaseCharacter;

UCLASS()
class MINIROGUE_TFG_API UMerchant : public UUserWidget
{
	GENERATED_BODY()

public:
	//Widget Elements
	//(TODO)


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
	
};
