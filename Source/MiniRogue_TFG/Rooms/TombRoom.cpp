// Fill out your copyright notice in the Description page of Project Settings.


#include "TombRoom.h"
#include "Components/StaticMeshComponent.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "MiniRogue_TFG/Characters/MonsterBase.h"
#include "MiniRogue_TFG/Enumerates/NegativeState.h"
#include "Animation/AnimSequence.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "MiniRogue_TFG/MiniRogue_TFGGameModeBase.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/Engine.h"
#include "MiniRogue_TFG/Dice.h"
#include "Components/ChildActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/TextRenderComponent.h"
#include "MiniRogue_TFG/MyGameInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "MiniRogue_TFG/Characters/RogueCharacter.h"
#include "Engine/EngineTypes.h"
#include "UObject/ConstructorHelpers.h"

ATombRoom::ATombRoom() {
	PrimaryActorTick.bCanEverTick = true;

	MonsterSpawned = CreateDefaultSubobject<UChildActorComponent>("MonsterSpawned");
	MonsterSpawned->SetupAttachment(GetRootComponent());
	DiceRespawn = CreateDefaultSubobject<USphereComponent>("DiceRespawnPoint");
	DiceRespawn->SetupAttachment(GetRootComponent());
	Search_Button = CreateDefaultSubobject<UStaticMeshComponent>("Search Button");
	Search_Button->SetupAttachment(GetRootComponent());
	Search_Button->OnClicked.AddDynamic(this, &ATombRoom::OnClickedSearchButton);
	Text1 = CreateDefaultSubobject<UTextRenderComponent>("Search Text");
	Text1->SetupAttachment(Search_Button);
	Combat_Button = CreateDefaultSubobject<UStaticMeshComponent>("Combat Button");
	Combat_Button->SetupAttachment(GetRootComponent());
	Combat_Button->OnClicked.AddDynamic(this, &ATombRoom::OnClickedCombatButton);
	Text2 = CreateDefaultSubobject<UTextRenderComponent>("Combat Text");
	Text2->SetupAttachment(Combat_Button);
	RoomCollision->OnComponentBeginOverlap.AddDynamic(this, &ATombRoom::OnBeginOverlap);
}
void ATombRoom::BeginPlay()
{
	Super::ABaseRoom::BeginPlay();
	Combat_Button->SetVisibility(false, true);
	Search_Button->SetVisibility(false, true);
	AMiniRogue_TFGGameModeBase* gamemode = Cast<AMiniRogue_TFGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (gamemode) {
		GM = gamemode;
	}
	Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Message->SetVisibility(false, true);
}

void ATombRoom::Tick(float DeltaTime)
{
	Super::ABaseRoom::Tick(DeltaTime);
}

void ATombRoom::RoomBehavior()
{
	Search_Button->SetVisibility(true, true);
	GetPlayerLevel(Character);
}

void ATombRoom::GetPlayerLevel(ABaseCharacter* Player)
{
	if (Player->Exp >= 18) {
		PlayerLevel = 3;
	}
	else if (Player->Exp >= 6) {
		PlayerLevel = 2;
	}
	else {
		PlayerLevel = 1;
	}
}

void ATombRoom::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor);

	if (Player) {
		Character = Player;
		ARogueCharacter* Rogue = Cast<ARogueCharacter>(Player);
		if (Rogue) {
			if (Rogue->EvasionActivated) {
				this->EventFinishRoom();
				Rogue->EvasionActivated = false;
			}
			else {
				this->RoomBehavior();
				GetWorldTimerManager().SetTimer(CheckTimer, this, &ATombRoom::Check, 0.3f, true);
				GetWorldTimerManager().SetTimer(SearchTimer, this, &ATombRoom::WaitForSearchResults, 0.3f, true);
			}
		}
		else {
			this->RoomBehavior();
			GetWorldTimerManager().SetTimer(CheckTimer, this, &ATombRoom::Check, 0.3f, true);
			GetWorldTimerManager().SetTimer(SearchTimer, this, &ATombRoom::WaitForSearchResults, 0.3f, true);
		}
	}
}

void ATombRoom::OnClickedSearchButton(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
}

void ATombRoom::OnClickedCombatButton(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
}

void ATombRoom::Check()
{
}

void ATombRoom::WaitForSearchResults()
{
}

void ATombRoom::StartCombat()
{
}

void ATombRoom::PlayerTurn()
{
}

void ATombRoom::LaunchDicesForSearch()
{
	Search_Button->SetVisibility(false, true);
	Controller->bEnableClickEvents = false;
	//auto PlayerDiceClass = ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/PlayerDice.PlayerDice'"));
	if (PlayerDiceClass) {
		for (int i = 0; i < PlayerLevel; i++) {
			FVector Loc = FVector(DiceRespawn->GetRelativeLocation().X, DiceRespawn->GetRelativeLocation().Y + (i * -50), DiceRespawn->GetRelativeLocation().Z);
			FRotator Rot = FRotator(UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f));
			GetWorld()->SpawnActor<AActor>(PlayerDiceClass, Loc, Rot);
		}
	}
	//auto DungeonDiceClass = ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/DungeonDice.DungeonDice'"));
	if (DungeonDiceClass) {
		FVector Loc = FVector(DiceRespawn->GetRelativeLocation().X, DiceRespawn->GetRelativeLocation().Y + 100, DiceRespawn->GetRelativeLocation().Z);
		FRotator Rot = FRotator(UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f));
		GetWorld()->SpawnActor<AActor>(DungeonDiceClass, Loc, Rot);
	}
}

void ATombRoom::DestroyDicesForSearch()
{
	TArray<AActor*> playerDices;
	//auto PlayerDiceClass = ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/PlayerDice.PlayerDice'"));
	if (PlayerDiceClass) {
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerDiceClass, playerDices);
	}
	if (playerDices.Num() != 0) {
		for (int i = 0; i < playerDices.Num(); i++) {
			playerDices[i]->Destroy();
		}
	}
	TArray<AActor*> dungeonDices;
	//auto DungeonDiceClass= ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/DungeonDice.DungeonDice''"));
	if (DungeonDiceClass) {
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), DungeonDiceClass, dungeonDices);
	}
	if (dungeonDices.Num() != 0) {
		for (int j = 0; j < dungeonDices.Num(); j++) {
			dungeonDices[j]->Destroy();
		}
	}
	Controller->bEnableClickEvents = true;
}

void ATombRoom::LaunchDicesForCombat()
{
	Combat_Button->SetVisibility(false, true);
	Controller->bEnableClickEvents = false;
	//auto PlayerDiceClass = ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/PlayerDice.PlayerDice'"));
	if (PlayerDiceClass) {
		for (int i = 0; i < PlayerLevel; i++) {
			FVector Loc = FVector(DiceRespawn->GetRelativeLocation().X, DiceRespawn->GetRelativeLocation().Y + (i * -50), DiceRespawn->GetRelativeLocation().Z);
			FRotator Rot = FRotator(UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f));
			GetWorld()->SpawnActor<AActor>(PlayerDiceClass, Loc, Rot);
		}
	}
	//auto DungeonDiceClass = ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/DungeonDice.DungeonDice'"));
	if (DungeonDiceClass) {
		FVector Loc = FVector(DiceRespawn->GetRelativeLocation().X, DiceRespawn->GetRelativeLocation().Y + 100, DiceRespawn->GetRelativeLocation().Z);
		FRotator Rot = FRotator(UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f));
		GetWorld()->SpawnActor<AActor>(DungeonDiceClass, Loc, Rot);
	}
	if (Character->States.Contains(ENegativeState::Poisoned)) {
		//auto PoisonDiceClass = ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/PoisonDice.PoisonDice'"));
		if (PoisonDiceClass) {
			FVector Loc = FVector(DiceRespawn->GetRelativeLocation().X, DiceRespawn->GetRelativeLocation().Y + 200, DiceRespawn->GetRelativeLocation().Z);
			FRotator Rot = FRotator(UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f));
			GetWorld()->SpawnActor<AActor>(PoisonDiceClass, Loc, Rot);
		}
	}
	if (Character->States.Contains(ENegativeState::Cursed)) {
		//auto CurseDiceClass = ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/CurseDice.CurseDice'"));
		if (CurseDiceClass) {
			FVector Loc = FVector(DiceRespawn->GetRelativeLocation().X, DiceRespawn->GetRelativeLocation().Y + 300, DiceRespawn->GetRelativeLocation().Z);
			FRotator Rot = FRotator(UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f));
			GetWorld()->SpawnActor<AActor>(CurseDiceClass, Loc, Rot);
		}
	}
}

void ATombRoom::DestroyDicesForCombat()
{
	TArray<AActor*> playerDices;
	//auto PlayerDiceClass = ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/PlayerDice.PlayerDice'"));
	if (PlayerDiceClass) {
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerDiceClass, playerDices);
	}
	if (playerDices.Num() != 0) {
		for (int i = 0; i < playerDices.Num(); i++) {
			playerDices[i]->Destroy();
		}
	}
	TArray<AActor*> dungeonDices;
	//auto DungeonDiceClass= ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/DungeonDice.DungeonDice''"));
	if (DungeonDiceClass) {
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), DungeonDiceClass, dungeonDices);
	}
	if (dungeonDices.Num() != 0) {
		for (int j = 0; j < dungeonDices.Num(); j++) {
			dungeonDices[j]->Destroy();
		}
	}
	TArray<AActor*> poisonDices;
	//auto PoisonDiceClass= ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/PoisonDice.PoisonDice'"));
	if (Character->States.Contains(ENegativeState::Poisoned)) {
		if (PoisonDiceClass) {
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), PoisonDiceClass, poisonDices);
		}
		if (poisonDices.Num() != 0) {
			for (int k = 0; k < poisonDices.Num(); k++) {
				poisonDices[k]->Destroy();
			}
		}
	}
	TArray<AActor*> curseDices;
	//auto CurseDiceClass= ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/CurseDice.CurseDice'"));
	if (Character->States.Contains(ENegativeState::Cursed)) {
		if (CurseDiceClass) {
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), CurseDiceClass, curseDices);
		}
		if (curseDices.Num() != 0) {
			for (int w = 0; w < curseDices.Num(); w++) {
				curseDices[w]->Destroy();
			}
		}
		Combat_Button->SetVisibility(true, true);
		Controller->bEnableClickEvents = true;
	}
}
