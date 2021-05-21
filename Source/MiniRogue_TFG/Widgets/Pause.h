// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Pause.generated.h"

class UImage;
class UButton;
class UGameSettings;


UCLASS()
class MINIROGUE_TFG_API UPause : public UUserWidget
{
	GENERATED_BODY()

public:
	//Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		UGameSettings* SettingsUIRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetClass")
		TSubclassOf<UGameSettings> WidgetClass;
	//Widget variables
	UPROPERTY(meta = (BindWidget))
		UButton* PauseMenu_Button_Exit;
	UPROPERTY(meta = (BindWidget))
		UButton* PauseMenu_Button_Resume;
	UPROPERTY(meta = (BindWidget))
		UButton* PauseMenu_Button_Settings;
	UPROPERTY(meta = (BindWidget))
		UImage* BLOCK_CLIC_FONDO;



	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime) override;

	UFUNCTION()
		void OnClicked_Resume();
	UFUNCTION()
		void OnClicked_Settings();
	UFUNCTION()
		void OnClicked_Exit();

	
};
