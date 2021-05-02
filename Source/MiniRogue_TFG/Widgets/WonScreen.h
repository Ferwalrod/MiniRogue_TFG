// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WonScreen.generated.h"

class UButton;

UCLASS()
class MINIROGUE_TFG_API UWonScreen : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
		UButton* Button_38;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_71;

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime) override;

	UFUNCTION()
		void OnClicked_Button_38();
	UFUNCTION()
		void OnClicked_Button_71();
};
