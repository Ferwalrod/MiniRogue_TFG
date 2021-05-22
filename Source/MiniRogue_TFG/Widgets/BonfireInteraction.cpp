// Fill out your copyright notice in the Description page of Project Settings.


#include "BonfireInteraction.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "MiniRogue_TFG/MiniRogue_TFGGameModeBase.h"
#include "Engine/World.h"
#include "MiniRogue_TFG/MyGameInstance.h"
#include "GameFramework/PlayerController.h"

void UBonfireInteraction::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Food->OnClicked.AddDynamic(this, &UBonfireInteraction::OnClicked_Button_Food);
	Button_Exp->OnClicked.AddDynamic(this, &UBonfireInteraction::OnClicked_Button_Exp);
	Button_Hp->OnClicked.AddDynamic(this, &UBonfireInteraction::OnClicked_Button_Hp);
	Button_Accept->OnClicked.AddDynamic(this, &UBonfireInteraction::OnClicked_Accept);
}

void UBonfireInteraction::NativeTick(const FGeometry& Geometry, float DeltaTime)
{
	Super::NativeTick(Geometry, DeltaTime);
}

void UBonfireInteraction::ShowFocusedBorder(UImage* Border)
{
	Border_Food->SetVisibility(ESlateVisibility::Hidden);
	Border_Exp->SetVisibility(ESlateVisibility::Hidden);
	Border_Hp->SetVisibility(ESlateVisibility::Hidden);
	Border->SetVisibility(ESlateVisibility::Visible);
}

void UBonfireInteraction::OnClicked_Button_Food()
{
	RewardChosen = 1;
	ShowFocusedBorder(Border_Food);
}

void UBonfireInteraction::OnClicked_Button_Exp()
{
	RewardChosen = 0;
	ShowFocusedBorder(Border_Exp);
}

void UBonfireInteraction::OnClicked_Button_Hp()
{
	RewardChosen = 2;
	ShowFocusedBorder(Border_Hp);
}

void UBonfireInteraction::OnClicked_Accept()
{
	this->RemoveFromParent();
	FInputModeGameAndUI GUI;
	GUI.SetHideCursorDuringCapture(true);
	GUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (Controller) {
		Controller->SetInputMode(GUI);
		Controller->bShowMouseCursor = true;
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		ABaseCharacter* Player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (Player) {
			switch (RewardChosen) {
			case 0:
				Player->Exp = UKismetMathLibrary::Clamp(Player->Exp+1, 0, Player->MaxExp);

				break;
			case 1:
				Player->Food = UKismetMathLibrary::Clamp(Player->Food+1, 0, Player->MaxFood);

				break;
			case 2:
				Player->Health = UKismetMathLibrary::Clamp(Player->Health+2, 0, Player->MaxHealth);

				break;
			}
			Player->UpdateUserInterface();
			Controller->bEnableClickEvents = true;
			AMiniRogue_TFGGameModeBase* GM = Cast<AMiniRogue_TFGGameModeBase>(GetWorld()->GetAuthGameMode());
			UMyGameInstance* GI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
			if (GM && GI) {
				GM->RoomFinished = true;
				switch (GI->RoomIndex) {
				case 0:
					Player->BottomArrowVisibility = true;
					Player->RightArrowVisibility = true;
					break;
				case 1:
					Player->BottomArrowVisibility = true;
					Player->RightArrowVisibility = true;
					break;
				case 2:
					Player->BottomArrowVisibility = true;
					break;
				case 3:
					Player->BottomArrowVisibility = true;
					Player->RightArrowVisibility = true;
					break;
				case 4:
					Player->BottomArrowVisibility = true;
					Player->RightArrowVisibility = true;
					break;
				case 5:
					Player->BottomArrowVisibility = true;
					break;
				case 6:
					Player->RightArrowVisibility = true;
					break;
				case 7:
					Player->RightArrowVisibility = true;
					break;
				}
			}
		}
	}
}
