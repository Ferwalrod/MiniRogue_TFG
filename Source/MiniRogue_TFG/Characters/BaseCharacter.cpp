// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "MiniRogue_TFG/PotionObject.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "MiniRogue_TFG/Characters/MonsterBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "MiniRogue_TFG/MiniRogue_TFGGameModeBase.h"
#include "MiniRogue_TFG/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "MiniRogue_TFG/Widgets/UserInterface.h"
#include "Engine/World.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RightArrow = CreateDefaultSubobject<UStaticMeshComponent>("RightArrow");
	BottomArrow = CreateDefaultSubobject<UStaticMeshComponent>("BottomArrow");
	RightArrow->AttachTo(GetRootComponent());
	RightArrow->OnClicked.AddDynamic(this, &ABaseCharacter::OnClickedRightArrow);
	BottomArrow->AttachTo(GetRootComponent());
	BottomArrow->OnClicked.AddDynamic(this, &ABaseCharacter::OnClickedBottomArrow);

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseCharacter::SetupPlayer() {

	AMiniRogue_TFGGameModeBase* GM = Cast<AMiniRogue_TFGGameModeBase>(GetWorld()->GetAuthGameMode());
	GetWorldTimerManager().SetTimer(Timer, this, &ABaseCharacter::CheckArrowVisibilities, 1.f, true);
	if (GM) {
		FVector Center = GM->Center;
		APlayerController* Controllerel = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		Controllerel->bShowMouseCursor = true;
		Controllerel->bEnableClickEvents = true;
		BottomArrow->SetVisibility(BottomArrowVisibility);
		RightArrow->SetVisibility(RightArrowVisibility);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controllerel, Center);
		float YawRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Center).Yaw;
		this->GetMesh()->AddLocalRotation(FRotator(0.f, YawRot, 0.f));
		this->GetCapsuleComponent()->AddLocalRotation(FRotator(0.f, YawRot, 0.f));
	}

	//(TODO) ==== LOAD PLAYER DATA FROM GAME INSTANCE
	HUD = CreateWidget<UUserInterface>(UGameplayStatics::GetPlayerController(GetWorld(), 0), InterfaceClass);
	HUD->PlayerCharacter = this;
	HUD->UpdateInterface();
	HUD->AddToViewport();

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ABaseCharacter::CheckArrowVisibilities() {

	if (BottomArrowVisibility && RightArrowVisibility) {
		RightArrow->SetVisibility(true);
		BottomArrow->SetVisibility(true);
		GetWorldTimerManager().ClearTimer(Timer);

	}else if (BottomArrowVisibility) {
		BottomArrow->SetVisibility(true);
		GetWorldTimerManager().ClearTimer(Timer);
	}
	else if (RightArrowVisibility) {
		RightArrow->SetVisibility(true);
		GetWorldTimerManager().ClearTimer(Timer);
	}

}

void ABaseCharacter::OnClickedRightArrow(UPrimitiveComponent* TouchedComponent, FKey buttonPresed)
{
	AMiniRogue_TFGGameModeBase* GM = Cast<AMiniRogue_TFGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GM) {
		if (GM->RoomFinished && RightArrowVisibility) {
			APlayerController* Controllerel = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			FVector FinalLoc = GM->RightDoor;
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controllerel, FinalLoc);
			float YawRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), FinalLoc).Yaw;
			this->GetMesh()->AddLocalRotation(FRotator(0.f, YawRot, 0.f));
			this->GetCapsuleComponent()->AddLocalRotation(FRotator(0.f, YawRot, 0.f));
			Controllerel->bEnableClickEvents = false;
			BottomArrow->SetVisibility(false);
			RightArrow->SetVisibility(false);
		}
	}

}

void ABaseCharacter::OnClickedBottomArrow(UPrimitiveComponent* TouchedComponent, FKey buttonPresed)
{
	AMiniRogue_TFGGameModeBase* GM = Cast<AMiniRogue_TFGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GM) {
		if (GM->RoomFinished && BottomArrowVisibility) {
			APlayerController* Controllerel = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			FVector FinalLoc = GM->BottomDoor;
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controllerel, FinalLoc);
			float YawRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), FinalLoc).Yaw;
			this->GetMesh()->AddLocalRotation(FRotator(0.f, YawRot, 0.f));
			this->GetCapsuleComponent()->AddLocalRotation(FRotator(0.f, YawRot, 0.f));
			Controllerel->bEnableClickEvents = false;
			BottomArrow->SetVisibility(false);
			RightArrow->SetVisibility(false);
		}
	}
}

//Solo sirve para comprobar, eliminar cuando se implemente la habitacion base en C++
void ABaseCharacter::Debug()
{
	AMiniRogue_TFGGameModeBase* GM = Cast<AMiniRogue_TFGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GM) {
		RightArrowVisibility = true;
		BottomArrowVisibility = true;
		GM->RoomFinished = true;
		BottomArrow->SetVisibility(RightArrowVisibility);
		RightArrow->SetVisibility(BottomArrowVisibility);
	}

}

void ABaseCharacter::TakeDamageCpp(int Damage)
{
	if (Armor - Damage <= 0) {
		Health = Health - UKismetMathLibrary::Abs(Armor - Damage);
		Armor = 0;
		if (Health <= 0) {
			//UGameplayStatics::SetGamePaused(GetWorld(),false);
			//Add the game over screen and add to viewport
		}
	}
	else {
		Armor = Armor - Damage;
	}
}

void ABaseCharacter::UpdateUserInterface()
{
	HUD->UpdateInterface();
}

void ABaseCharacter::EquiptWeaponCpp(EWeaponType Weapon)
{
	switch (Weapon) {
	case EWeaponType::NoWeapon:
		currentWeapon = EWeaponType::NoWeapon;
		WeaponCharges = 0;
		break;
	case EWeaponType::Dagger:
		currentWeapon = EWeaponType::Dagger;
		WeaponCharges = 3;
		break;
	case EWeaponType::Longsword:
		currentWeapon = EWeaponType::Longsword;
		WeaponCharges = 2;
		break;
	case EWeaponType::BattleAxe:
		currentWeapon = EWeaponType::BattleAxe;
		WeaponCharges = 2;
		break;
	}
}

void ABaseCharacter::UseWeaponCpp()
{
	if (currentWeapon != EWeaponType::NoWeapon && isInCombat && WeaponCharges>0) {
		int DamageDeal=0;
		switch (currentWeapon) {
		case EWeaponType::Dagger:
			DamageDeal = 1;
			break;
		case EWeaponType::Longsword:
			DamageDeal = 2;
			break;
		case EWeaponType::BattleAxe:
			DamageDeal = 3;
			break;
		}
		UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
		if (GI) {
			if (GI->ActMonster) {
				GI->ActMonster->Live -= DamageDeal;
				GI->ActMonster->IsDead = GI->ActMonster->Live <= 0;
				WeaponCharges--;
			}
			else if (GI->ActBoss) {
				GI->ActBoss->Live -= DamageDeal;
				GI->ActBoss->IsDead = GI->ActBoss->Live <= 0;
				WeaponCharges--;
			}
			this->UpdateUserInterface();
		}

	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Debug", IE_Pressed, this, &ABaseCharacter::Debug);
}

