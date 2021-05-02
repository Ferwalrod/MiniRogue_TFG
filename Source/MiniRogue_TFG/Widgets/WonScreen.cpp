// Fill out your copyright notice in the Description page of Project Settings.


#include "WonScreen.h"
#include "Components/Button.h"
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"

void UWonScreen::NativeConstruct()
{
	Super::NativeConstruct();

	Button_38->OnClicked.AddDynamic(this, &UWonScreen::OnClicked_Button_38);
	Button_71->OnClicked.AddDynamic(this, &UWonScreen::OnClicked_Button_71);
}

void UWonScreen::NativeTick(const FGeometry& Geometry, float DeltaTime)
{
	Super::NativeTick(Geometry, DeltaTime);
}

void UWonScreen::OnClicked_Button_38()
{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Vuelves al menu principal"));
}

void UWonScreen::OnClicked_Button_71()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Te sales del juego"));

}
