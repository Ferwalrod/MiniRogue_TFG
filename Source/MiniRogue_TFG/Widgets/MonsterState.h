// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MonsterState.generated.h"

class UImage;
class UProgressBar;
class AMonsterBase;
class UTexture2D;
class UTextBlock;

UCLASS()
class MINIROGUE_TFG_API UMonsterState : public UUserWidget
{
	GENERATED_BODY()

public:

	
	UPROPERTY(meta = (BindWidget))
	UImage* Image_77;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar_106;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget Components")
	AMonsterBase* Monster;
	UPROPERTY(meta = (BindWidget))
	UImage* damage_type;
	UPROPERTY(BlueprintReadWrite)
	UTexture2D* DamageTexture;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Name_Text;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Floor;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Damage_text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget Components")
	UTexture2D* Poison;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget Components")
	UTexture2D* Curse;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget Components")
	UTexture2D* Blind;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget Components")
	UTexture2D* Weakness;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget Components")
	UTexture2D* NoArmor;
public:
	void NativeConstruct() override;
	void NativeTick(const FGeometry& Geometry, float DeltaTime) override;


	UFUNCTION()
	FText GetNameText();
	UFUNCTION()
	FText GetFloorText();
	UFUNCTION()
	FText GetDamageText();
	UFUNCTION()
	float GetPercent();

	void SetMonsterOwner(AMonsterBase* Owner);
};
