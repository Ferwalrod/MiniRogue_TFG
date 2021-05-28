// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameSettings.generated.h"

class UImage;
class UButton;
class UUserWidget;
class USlider;
class UEditableText;
class UPause;

UCLASS()
class MINIROGUE_TFG_API UGameSettings : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		UUserWidget* ParentWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		UPause* PauseUIRef;

	//Widget variables
	UPROPERTY(meta = (BindWidget))
		UButton* Button_ReturnPauseMenu;
	UPROPERTY(meta = (BindWidget))
		UEditableText* EditText_PlayerName;
	UPROPERTY(meta = (BindWidget))
		UImage* IMG_Avatar;
	UPROPERTY(meta = (BindWidget))
		USlider* Volume_BrightnessSlider;
	UPROPERTY(meta = (BindWidget))
		USlider* Volume_Slider;


	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime) override;
	void SetParentWidget(UUserWidget* Parent);

	UFUNCTION()
		void OnClicked_ReturnPauseMenu();
	
};
