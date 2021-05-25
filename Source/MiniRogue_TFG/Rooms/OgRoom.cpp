// Fill out your copyright notice in the Description page of Project Settings.


#include "OgRoom.h"
#include "Components/StaticMeshComponent.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "MiniRogue_TFG/Characters/MonsterBase.h"
#include "MiniRogue_TFG/Enumerates/NegativeState.h"
#include "MiniRogue_TFG/Rooms/BaseRoom.h"
#include "Animation/AnimSequence.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "MiniRogue_TFG/MiniRogue_TFGGameModeBase.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/Engine.h"
#include "MiniRogue_TFG/Characters/OgRemains.h"
#include "MiniRogue_TFG/Widgets/WonScreen.h"
#include "MiniRogue_TFG/Widgets/OgState.h"
#include "MiniRogue_TFG/Characters/OgRemains.h"
//#include "Engine/Blueprint.h"
#include "MiniRogue_TFG/Dice.h"
#include "Components/ChildActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/PlayerController.h"
#include "Components/TextRenderComponent.h"
#include "MiniRogue_TFG/MyGameInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "MiniRogue_TFG/Characters/RogueCharacter.h"
#include "Engine/EngineTypes.h"
#include "UObject/ConstructorHelpers.h"

AOgRoom::AOgRoom() {

	MonsterSpawned = CreateDefaultSubobject<UChildActorComponent>("MonsterSpawned");
	MonsterSpawned->SetupAttachment(GetRootComponent());
	DiceRespawn = CreateDefaultSubobject<USphereComponent>("DiceRespawnPoint");
	DiceRespawn->SetupAttachment(GetRootComponent());
	Plane = CreateDefaultSubobject<UStaticMeshComponent>("Plane");
	Plane->SetupAttachment(GetRootComponent());
	Plane->SetRelativeLocation(FVector(0.f, 140.f, 290.f));
	Plane->OnClicked.AddDynamic(this, &AOgRoom::OnClickedButton);
	Text = CreateDefaultSubobject<UTextRenderComponent>("TextRender");
	Text->SetupAttachment(Plane);
	RoomCollision->OnComponentBeginOverlap.AddDynamic(this, &AOgRoom::OnBeginOverlap);
	Ladders = CreateDefaultSubobject<UBoxComponent>("Ladders");
	Ladders->SetupAttachment(GetRootComponent());
	Ladders->OnComponentBeginOverlap.AddDynamic(this, &AOgRoom::OnLaddersOverlap);
}
void AOgRoom::BeginPlay()
{
	Super::ABaseRoom::BeginPlay();
	Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AMiniRogue_TFGGameModeBase* gamemode = Cast<AMiniRogue_TFGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (gamemode) {
		GM = gamemode;
	}
}

void AOgRoom::Tick(float DeltaTime)
{
	Super::ABaseRoom::Tick(DeltaTime);
}

void AOgRoom::RoomBehavior()
{
	if (GI->LevelIndex == 2) {
		IsFinalLevel = true;
		MonsterSpawned->SetChildActorClass(MonsterClass);
		MonsterSpawned->CreateChildActor();
		AOgRemains* Og = Cast<AOgRemains>(MonsterSpawned->GetChildActor());
		if (Og) {
			Og->InitializePhase1();
			FinalBoss = Og;
			GetPlayerLevel(Character);
			StartCombat();
		}
	}
	else {
		IsFinalLevel = false;
		NextLevel();
	}
}

void AOgRoom::GetPlayerLevel(ABaseCharacter* Player)
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

void AOgRoom::NextLevel()
{
	Controller->bEnableClickEvents = false;
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, Ladders->GetComponentLocation());
}

void AOgRoom::Check()
{
	if (Character->States.Contains(ENegativeState::Poisoned) && Character->States.Contains(ENegativeState::Cursed)) {
		ExpectedDices = 4;
	}
	else if (Character->States.Contains(ENegativeState::Poisoned)) {
		ExpectedDices = 3;
	}
	else if (Character->States.Contains(ENegativeState::Cursed)) {
		ExpectedDices = 3;
	}
	else {
		ExpectedDices = 2;
	}
	if (CombatEnded) {
		GetWorldTimerManager().ClearTimer(Timer);
		this->EventFinishRoom();
		
	}
}

void AOgRoom::PlayerTurn()
{
	if (FinalBoss->IsDead) {
		if (FinalBoss->PhaseNumber == 2) {
			CombatEnded = true;
			GetWorldTimerManager().ClearTimer(CombatTimer);
			DestroyDices();
			Plane->SetVisibility(false, true);
			FinalBoss->GetMesh()->PlayAnimation(FinalBoss->AnimDead, false);
			FLatentActionInfo info;
			info.CallbackTarget = this;
			info.Linkage = 0;
			UKismetSystemLibrary::Delay(GetWorld(), 3.f, info);
			MonsterSpawned->SetChildActorClass(nullptr);
			MonsterSpawned->CreateChildActor();
			Controller->bEnableClickEvents = false;
			Character->RightArrowVisibility = false;
			Character->BottomArrowVisibility = false;
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, Ladders->GetRelativeLocation());

		}
		else {
			FinalBoss->InitializePhase2();
			GM->Results.Empty(ExpectedDices);
			DestroyDices();
		}
	}
	else {
		if (GM->Results.Num() == ExpectedDices) {
			int poison = 0;
			int curse = 0;
			if (GM->Results.Find(EDiceType::Poison) != nullptr) {
				poison = *GM->Results.Find(EDiceType::Poison);
			}
			if (GM->Results.Find(EDiceType::Curse) != nullptr) {
				curse = *GM->Results.Find(EDiceType::Curse);
			}
			Character->Health = Character->Health + poison;
			ARogueCharacter* Rogue1 = Cast<ARogueCharacter>(Character);
			if (Rogue1 && Rogue1->BackStabActivated) {
				FinalBoss->Live = FinalBoss->Live - (2 * (*GM->Results.Find(EDiceType::Player)) + curse);
				Rogue1->BackStabActivated = false;
			}
			else {
				FinalBoss->Live = FinalBoss->Live - (*GM->Results.Find(EDiceType::Player) + curse);
			}
			FinalBoss->UpdateOgState();
			if (FinalBoss->IsDead || FinalBoss->Live <= 0) {
				if (FinalBoss->PhaseNumber == 2) {
					CombatEnded = true;
					GetWorldTimerManager().ClearTimer(CombatTimer);
					DestroyDices();
					Plane->SetVisibility(false, true);
				    FinalBoss->GetMesh()->PlayAnimation(FinalBoss->AnimDead, false);
					FLatentActionInfo info;
					info.CallbackTarget = this;
					info.Linkage = 0;
		            UKismetSystemLibrary::Delay(GetWorld(), 3.f, info);
					MonsterSpawned->SetChildActorClass(nullptr);
					MonsterSpawned->CreateChildActor();
					Controller->bEnableClickEvents = false;
					Character->RightArrowVisibility = false;
					Character->BottomArrowVisibility = false;
					UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, Ladders->GetRelativeLocation());

				}
				else {
					FinalBoss->InitializePhase2();
					GM->Results.Empty(ExpectedDices);
					DestroyDices();
				}
			}
			else {
				if (FinalBoss->IsMonsterFrozen) {
					GM->Results.Empty(ExpectedDices);
					Character->UpdateUserInterface();
					FinalBoss->IsMonsterFrozen = false;
					DestroyDices();
				}
				else {
					FinalBoss->GetMesh()->PlayAnimation(FinalBoss->AnimCombat, false);
					if (*GM->Results.Find(EDiceType::Dungeon) != 1) {
						switch (FinalBoss->DamageType) {
						case EAttackState::PoisonAttack:
							Character->States.Add(ENegativeState::Poisoned);
							Character->TakeDamageCpp(FinalBoss->Damage);
							GM->Results.Empty(ExpectedDices);
							Character->UpdateUserInterface();
							DestroyDices();
							break;
						case EAttackState::CurseAttack:
							Character->States.Add(ENegativeState::Cursed);
							Character->TakeDamageCpp(FinalBoss->Damage);
							GM->Results.Empty(ExpectedDices);
							Character->UpdateUserInterface();
							DestroyDices();
							break;
						}
					}
					else {
						GM->Results.Empty(ExpectedDices);
						Character->UpdateUserInterface();
						DestroyDices();
					}
				}
			}
		}
	}
}

void AOgRoom::StartCombat()
{
	Text->SetVisibility(true, true);
	Plane->SetVisibility(true, true);
	GetWorldTimerManager().SetTimer(CombatTimer, this, &AOgRoom::PlayerTurn, 0.4f, true);
}

void AOgRoom::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor);

	if (Player) {
		Character = Player;
		this->RoomBehavior();
		Character->isInCombat = true;
		Character->UpdateUserInterface();
		GetWorldTimerManager().SetTimer(Timer, this, &AOgRoom::Check, 0.3f, true);
		
	}
}

void AOgRoom::OnClickedButton(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	LaunchDices();
}

void AOgRoom::OnLaddersOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor);
	if (Player) {
		GetWorldTimerManager().ClearTimer(Timer);
		if (IsFinalLevel) {
			CreateWidget<UWonScreen>(Controller, WonScreenClass)->AddToViewport();
		}
		else {
			if (Character->Food != 0) {
				Character->Food--;
			}
			else {
				Character->Health -= 3;
			}
			GI->LevelIndex++;
			GI->RoomIndex = 0;
			
			/*
			=====(TODO)======SAVE PLAYER DATA
			=======(TODO)==== OPEN NEXT LEVEL
			*/
		}
	}
}

void AOgRoom::DestroyDices()
{
	TArray<AActor*> playerDices;
	if (PlayerDiceClass) {
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerDiceClass, playerDices);
	}
	if (playerDices.Num() != 0) {
		for (int i = 0; i < playerDices.Num(); i++) {
			playerDices[i]->Destroy();
		}
	}
	TArray<AActor*> dungeonDices;
	if (DungeonDiceClass) {
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), DungeonDiceClass, dungeonDices);
	}
	if (dungeonDices.Num() != 0) {
		for (int j = 0; j < dungeonDices.Num(); j++) {
			dungeonDices[j]->Destroy();
		}
	}
	TArray<AActor*> poisonDices;
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
	if (Character->States.Contains(ENegativeState::Cursed)) {
		if (CurseDiceClass) {
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), CurseDiceClass, curseDices);
		}
		if (curseDices.Num() != 0) {
			for (int w = 0; w < curseDices.Num(); w++) {
				curseDices[w]->Destroy();
			}
		}
	}
	Plane->SetVisibility(true, true);
	Controller->bEnableClickEvents = true;
}

void AOgRoom::LaunchDices()
{
	Plane->SetVisibility(false, true);
	Controller->bEnableClickEvents = false;
	if (PlayerDiceClass) {
		for (int i = 0; i < PlayerLevel; i++) {
			FVector Loc = FVector(DiceRespawn->GetRelativeLocation().X, DiceRespawn->GetRelativeLocation().Y + (i * -50), DiceRespawn->GetRelativeLocation().Z);
			FRotator Rot = FRotator(UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f));
			GetWorld()->SpawnActor<AActor>(PlayerDiceClass, Loc, Rot);
		}
	}
	if (DungeonDiceClass) {
		FVector Loc = FVector(DiceRespawn->GetRelativeLocation().X, DiceRespawn->GetRelativeLocation().Y + 100, DiceRespawn->GetRelativeLocation().Z);
		FRotator Rot = FRotator(UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f));
		GetWorld()->SpawnActor<AActor>(DungeonDiceClass, Loc, Rot);
	}
	if (Character->States.Contains(ENegativeState::Poisoned)) {
		if (PoisonDiceClass) {
			FVector Loc = FVector(DiceRespawn->GetRelativeLocation().X, DiceRespawn->GetRelativeLocation().Y + 200, DiceRespawn->GetRelativeLocation().Z);
			FRotator Rot = FRotator(UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f));
			GetWorld()->SpawnActor<AActor>(PoisonDiceClass, Loc, Rot);
		}
	}
	if (Character->States.Contains(ENegativeState::Cursed)) {
		if (CurseDiceClass) {
			FVector Loc = FVector(DiceRespawn->GetRelativeLocation().X, DiceRespawn->GetRelativeLocation().Y + 300, DiceRespawn->GetRelativeLocation().Z);
			FRotator Rot = FRotator(UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f));
			GetWorld()->SpawnActor<AActor>(CurseDiceClass, Loc, Rot);
		}
	}
}
