// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterRoom.h"
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
//#include "Engine/Blueprint.h"
#include "MiniRogue_TFG/Dice.h"
#include "Components/ChildActorComponent.h"
#include "Components/PrimitiveComponent.h"
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


AMonsterRoom::AMonsterRoom() {
	PrimaryActorTick.bCanEverTick = true;
	MonsterSpawned = CreateDefaultSubobject<UChildActorComponent>("MonsterSpawned");
	MonsterSpawned->SetupAttachment(GetRootComponent());
	MonsterSpawned->SetRelativeLocation(FVector(220.f, 0.f, 95.f));
	MonsterSpawned->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	DiceRespawn = CreateDefaultSubobject<USphereComponent>("DiceRespawnPoint");
	DiceRespawn->SetupAttachment(GetRootComponent());
	DiceRespawn->SetRelativeLocation(FVector(-145.f,200.f,375.f));
	Plane = CreateDefaultSubobject<UStaticMeshComponent>("Plane");
	Plane->SetupAttachment(GetRootComponent());
	Plane->SetRelativeLocation(FVector(0.f,140.f,290.f));
	Plane->OnClicked.AddDynamic(this, &AMonsterRoom::OnClickedButton);
	Text = CreateDefaultSubobject<UTextRenderComponent>("TextRender");
	Text->SetupAttachment(Plane);
	RoomCollision->OnComponentBeginOverlap.AddDynamic(this, &AMonsterRoom::OnBeginOverlap);

}
void AMonsterRoom::BeginPlay()
{
	Super::ABaseRoom::BeginPlay();
	Plane->SetVisibility(false, true);
	AMiniRogue_TFGGameModeBase* gamemode = Cast<AMiniRogue_TFGGameModeBase>(GetWorld()->GetAuthGameMode());
		if (gamemode) {
			GM = gamemode;
		}
		Controller = UGameplayStatics::GetPlayerController(GetWorld(),0);
	    
}

void AMonsterRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterRoom::RoomBehavior()
{
	MonsterSpawned->SetChildActorClass(MonsterClass);
	MonsterSpawned->CreateChildActor();
	AMonsterBase* MonsterCasted = Cast<AMonsterBase>(MonsterSpawned->GetChildActor());
	if (MonsterCasted) {
		MonsterCasted->InitializeMonster();
		Monster = MonsterCasted;
		

		GI->ActMonster = MonsterCasted;
		this->GetPlayerLevel(Character);
		this->StartCombat();
		
		
	}
}

void AMonsterRoom::GetPlayerLevel(ABaseCharacter* Player)
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

void AMonsterRoom::StartCombat()
{
	Text->SetVisibility(true, true);
	Plane->SetVisibility(true, true);
	GetWorldTimerManager().SetTimer(CombatTimer, this, &AMonsterRoom::PlayerTurn, 0.4f, true);
}

void AMonsterRoom::Check()
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

void AMonsterRoom::PlayerTurn()
{
	
	if (Monster->IsDead) {
		CombatEnded = true;
		Character->isInCombat = false;
		Character->UpdateUserInterface();
		GetWorldTimerManager().ClearTimer(CombatTimer);
		DestroyDices();
		Plane->SetVisibility(false, true);
		Monster->GetMesh()->PlayAnimation(Monster->AnimDead, false);
		FLatentActionInfo info;
		UKismetSystemLibrary::Delay(GetWorld(),3.f,info);
		Character->Exp = UKismetMathLibrary::Clamp(Monster->Reward + Character->Exp, 0, Character->MaxExp);
		MonsterSpawned->SetChildActorClass(nullptr);
		MonsterSpawned->CreateChildActor();
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
				Monster->Live = Monster->Live - (2*(*GM->Results.Find(EDiceType::Player)) +curse);
				Rogue1->BackStabActivated=false;
			}
			else {
				Monster->Live = Monster->Live - (*GM->Results.Find(EDiceType::Player) + curse);
			}
			Monster->UpdateMonsterState();
			if (Monster->IsDead || Monster->Live <= 0) {
				CombatEnded = true;
				Character->isInCombat = false;
				Character->UpdateUserInterface();
				GetWorldTimerManager().ClearTimer(CombatTimer);
				DestroyDices();
				Plane->SetVisibility(false, true);
				Monster->GetMesh()->PlayAnimation(Monster->AnimDead, false);
				
				FLatentActionInfo info;
				UKismetSystemLibrary::Delay(GetWorld(), 3.f, info);
				Character->Exp = UKismetMathLibrary::Clamp(Monster->Reward + Character->Exp, 0, Character->MaxExp);
				MonsterSpawned->SetChildActorClass(nullptr);
				MonsterSpawned->CreateChildActor();
			}
			else {
				if (Monster->IsMonsterFrozen) {
					GM->Results.Empty(ExpectedDices);
					Character->UpdateUserInterface();
					Monster->IsMonsterFrozen = false;
					DestroyDices();
				}
				else {
					Monster->GetMesh()->PlayAnimation(Monster->AnimCombat, false);
					if (*GM->Results.Find(EDiceType::Dungeon) != 1) {
						switch (Monster->DamageType) {
						case EAttackState::PoisonAttack:
							Character->States.Add(ENegativeState::Poisoned);
							Character->TakeDamageCpp(Monster->Damage);
							GM->Results.Empty(ExpectedDices);
							Character->UpdateUserInterface();
							DestroyDices();
							break;
						case EAttackState::CurseAttack:
							Character->States.Add(ENegativeState::Cursed);
							Character->TakeDamageCpp(Monster->Damage);
							GM->Results.Empty(ExpectedDices);
							Character->UpdateUserInterface();
							DestroyDices();
							break;
						case EAttackState::BlindAttack:
							Character->States.Add(ENegativeState::Blinded);
							Character->TakeDamageCpp(Monster->Damage);
							GM->Results.Empty(ExpectedDices);
							Character->UpdateUserInterface();
							DestroyDices();
							break;
						case EAttackState::WeaknessAttack:
							Character->Exp--;
							Character->TakeDamageCpp(Monster->Damage);
							GM->Results.Empty(ExpectedDices);
							Character->UpdateUserInterface();
							DestroyDices();
							break;
						case EAttackState::NoArmorAttack:
							Character->TakeDamageCpp(Monster->Damage);
							GM->Results.Empty(ExpectedDices);
							Character->UpdateUserInterface();
							DestroyDices();
							break;
						case EAttackState::NoneStateAttack:
							Character->TakeDamageCpp(Monster->Damage);
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

void AMonsterRoom::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor);

	if (Player) {
		Character = Player;
		ARogueCharacter* Rogue = Cast<ARogueCharacter>(Player);
		if (Rogue) {
			if (Rogue->EvasionActivated) {
				this->EventFinishRoom();
				Rogue->EvasionActivated = false;
			}else {
				this->RoomBehavior();
				Character->isInCombat = true;
				Character->UpdateUserInterface();
				GetWorldTimerManager().SetTimer(Timer,this, &AMonsterRoom::Check,0.3f,true);
			}
		}else {
			this->RoomBehavior();
			Character->isInCombat = true;
			Character->UpdateUserInterface();
			GetWorldTimerManager().SetTimer(Timer, this, &AMonsterRoom::Check, 0.3f, true);
		}
	}
}

void AMonsterRoom::OnClickedButton(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	this->LaunchDices();
}

void AMonsterRoom::DestroyDices()
{
	TArray<AActor*> playerDices;
	
	if (PlayerDiceClass) {
		UGameplayStatics::GetAllActorsOfClass(GetWorld(),PlayerDiceClass, playerDices);
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

void AMonsterRoom::LaunchDices()
{
	Plane->SetVisibility(false, true);
	Controller->bEnableClickEvents = false;
	
	if (PlayerDiceClass) {
		for (int i = 0; i < PlayerLevel ; i++) {
			FVector Loc = FVector(DiceRespawn->GetRelativeLocation().X, DiceRespawn->GetRelativeLocation().Y+(i*-50), DiceRespawn->GetRelativeLocation().Z);
			FRotator Rot = FRotator(UKismetMathLibrary::RandomFloatInRange(0.f,360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f));
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
	if(Character->States.Contains(ENegativeState::Cursed)){
		
		if (CurseDiceClass) {
			FVector Loc = FVector(DiceRespawn->GetRelativeLocation().X, DiceRespawn->GetRelativeLocation().Y + 300, DiceRespawn->GetRelativeLocation().Z);
			FRotator Rot = FRotator(UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f));
			GetWorld()->SpawnActor<AActor>(CurseDiceClass, Loc, Rot);
		}
	}
}
