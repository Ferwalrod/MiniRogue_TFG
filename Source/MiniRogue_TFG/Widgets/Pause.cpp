// Fill out your copyright notice in the Description page of Project Settings.


#include "Pause.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "MiniRogue_TFG/Widgets/GameSettings.h"
#include "MiniRogue_TFG/Widgets/Inventory.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "MiniRogue_TFG/MyGameInstance.h"
#include "MiniRogue_TFG/MiniRogue_TFGGameModeBase.h"

void UPause::NativeConstruct() {

	Super::NativeConstruct();
	PauseMenu_Button_Resume->OnClicked.AddDynamic(this, &UPause::OnClicked_Resume);
	PauseMenu_Button_Settings->OnClicked.AddDynamic(this, &UPause::OnClicked_Settings);
	PauseMenu_Button_Exit->OnClicked.AddDynamic(this, &UPause::OnClicked_Exit);
}

void UPause::NativeTick(const FGeometry& Geometry, float DeltaTime)
{
	Super::NativeTick(Geometry, DeltaTime);
}

void UPause::OnClicked_Resume()
{
	this->RemoveFromParent();
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FInputModeGameAndUI GUI;
	GUI.SetHideCursorDuringCapture(true);
	GUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	Controller->SetInputMode(GUI);
	Controller->bShowMouseCursor = true;
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UPause::OnClicked_Settings()
{

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (SettingsUIRef) {
		SettingsUIRef->SetParentWidget(this);
		this->RemoveFromParent();
		SettingsUIRef->AddToViewport();
		FInputModeGameAndUI GUI;
		GUI.SetHideCursorDuringCapture(true);
		GUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		Controller->SetInputMode(GUI);
	}
	else {
		SettingsUIRef = CreateWidget<UGameSettings>(Controller, WidgetClass);
		SettingsUIRef->SetParentWidget(this);
		this->RemoveFromParent();
		SettingsUIRef->AddToViewport();
		FInputModeGameAndUI GUI;
		GUI.SetHideCursorDuringCapture(true);
		GUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		Controller->SetInputMode(GUI);
		
	}
}

void UPause::OnClicked_Exit()
{
	//Implement quit game
}


