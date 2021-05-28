// Fill out your copyright notice in the Description page of Project Settings.


#include "TreasureInteraction1.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "MiniRogue_TFG/MiniRogue_TFGGameModeBase.h"
#include "MiniRogue_TFG/Widgets/TreasureInteraction2.h"
#include "Engine/World.h"
#include "MiniRogue_TFG/MyGameInstance.h"
#include "GameFramework/PlayerController.h"

void UTreasureInteraction1::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Accept->OnClicked.AddDynamic(this, &UTreasureInteraction1::OnClicked_Accept);
	
}

void UTreasureInteraction1::NativeTick(const FGeometry& Geometry, float DeltaTime)
{
	Super::NativeTick(Geometry, DeltaTime);
}

void UTreasureInteraction1::OnClicked_Accept()
{
	this->RemoveFromParent();
	UTreasureInteraction2* Widget = CreateWidget<UTreasureInteraction2>(UGameplayStatics::GetPlayerController(GetWorld(), 0), SecondWidgetClass);
	Widget->AddToViewport();

}
