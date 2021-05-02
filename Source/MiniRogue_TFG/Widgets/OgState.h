// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OgState.generated.h"

class AOgRemains;
class UImage;
class UTextBlock;
class UProgressBar;
UCLASS()
class MINIROGUE_TFG_API UOgState : public UUserWidget
{
	GENERATED_BODY()

public:


	UPROPERTY(meta = (BindWidget))
		UImage* Image_77;
	UPROPERTY(meta = (BindWidget))
		UProgressBar* ProgressBar_106;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget Components")
		AOgRemains* Og;
	UPROPERTY(meta = (BindWidget))
		UImage* damage_type;
	UPROPERTY(BlueprintReadWrite)
		UTexture2D* DamageTexture;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Name_Text;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Phase;
	UPROPERTY(meta = (BindWidget))
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
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime) override;


	UFUNCTION()
		FText GetNameText();
	UFUNCTION()
		FText GetPhaseText();
	UFUNCTION()
		FText GetDamageText();
	UFUNCTION(BlueprintCallable)
		float GetPercent();

	void SetMonsterOwner(AOgRemains* Owner);
	void UpdateWidget();
	
};
