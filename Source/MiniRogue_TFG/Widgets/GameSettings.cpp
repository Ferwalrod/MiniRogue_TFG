// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSettings.h"
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

void UGameSettings::NativeConstruct()
{
	Super::NativeConstruct();
	Button_ReturnPauseMenu->OnClicked.AddDynamic(this, &UGameSettings::OnClicked_ReturnPauseMenu);
}

void UGameSettings::NativeTick(const FGeometry& Geometry, float DeltaTime)
{
	Super::NativeTick(Geometry, DeltaTime);
}

void UGameSettings::SetParentWidget(UUserWidget* Parent)
{
	ParentWidget = Parent;
}

void UGameSettings::OnClicked_ReturnPauseMenu()
{
	this->RemoveFromParent();
	ParentWidget->AddToViewport();
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FInputModeGameAndUI GUI;
	GUI.SetHideCursorDuringCapture(true);
	GUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	Controller->SetInputMode(GUI);
}
