// Fill out your copyright notice in the Description page of Project Settings.


#include "ShrineInteraction1.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "MiniRogue_TFG/Dice.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Components/SphereComponent.h"

void UShrineInteraction1::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Normal_Pray->OnClicked.AddDynamic(this, &UShrineInteraction1::OnClicked_Normal_Pray);
	Button_Fervorous_Pray->OnClicked.AddDynamic(this, &UShrineInteraction1::OnClicked_Fervorous_Pray);
	
	ABaseCharacter* Character = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Character) {
		PlayerCharacter = Character;
		if (PlayerCharacter->Gold <= 0) {
			Button_Fervorous_Pray->RemoveFromParent();
		}
	}
}

void UShrineInteraction1::NativeTick(const FGeometry& Geometry, float DeltaTime)
{
	Super::NativeTick(Geometry, DeltaTime);
}

void UShrineInteraction1::SetRespawnPoint(USphereComponent* Point)
{
	RespawnPoint = Point;
}

void UShrineInteraction1::Check()
{
}

void UShrineInteraction1::OnClicked_Normal_Pray()
{
	Result = 0;
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	//===(TODO) UPDATE HUD OF THE CHARACTER
	ThrowDice();
	this->RemoveFromParent();
	GetWorldTimerManager().SetTimer(Timer, this, &UShrineInteraction1::Check, 0.8f, true);
	
}

void UShrineInteraction1::OnClicked_Fervorous_Pray()
{
	Result = 0;
	PlayerCharacter->Gold--;
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	//===(TODO) UPDATE HUD OF THE CHARACTER
	ThrowDice();
	this->RemoveFromParent();
	GetWorldTimerManager().SetTimer(Timer, this, &UShrineInteraction1::Check, 0.8f, true);

}

void UShrineInteraction1::ThrowDice()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Controller->bEnableClickEvents = false;
	FVector Loc = RespawnPoint->GetRelativeLocation();
	Loc.Y += 150.f;
	FRotator Rot = FRotator(UKismetMathLibrary::RandomFloatInRange(0.f,360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f));
	ADice* Dice=Cast<ADice>(GetWorld()->SpawnActor<AActor>(DiceClass, Loc, Rot));
	if (Dice) {
		DungeonDice = Dice;
		DungeonDice->Dice->AddImpulse(FVector(0.f, -500.f, 0.f));
	}
}
