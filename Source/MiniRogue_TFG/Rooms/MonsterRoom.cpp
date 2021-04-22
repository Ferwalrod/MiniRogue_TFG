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
#include "Components/ChildActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/TextRenderComponent.h"
#include "MiniRogue_TFG/Characters/MonsterBase.h"
#include "MiniRogue_TFG/MyGameInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MiniRogue_TFG/Characters/RogueCharacter.h"
#include "UObject/ConstructorHelpers.h"


AMonsterRoom::AMonsterRoom() {
	PrimaryActorTick.bCanEverTick = true;
	MonsterSpawned = CreateDefaultSubobject<UChildActorComponent>("MonsterSpawned");
	MonsterSpawned->AttachTo(GetRootComponent());
	DiceRespawn = CreateDefaultSubobject<USphereComponent>("DiceRespawnPoint");
	DiceRespawn->AttachTo(GetRootComponent());
	Plane = CreateDefaultSubobject<UStaticMeshComponent>("Plane");
	Plane->AttachTo(GetRootComponent());
	Plane->OnClicked.AddDynamic(this, &AMonsterRoom::OnClickedButton);
	Text = CreateDefaultSubobject<UTextRenderComponent>("TextRender");
	Text->AttachTo(Plane);
	RoomCollision->OnComponentBeginOverlap.AddDynamic(this, &AMonsterRoom::OnOverlap);
}
void AMonsterRoom::BeginPlay()
{
	Super::BeginPlay();
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
	AMonsterBase* MonsterCasted = Cast<AMonsterBase>(MonsterSpawned->GetChildActor());
	if (MonsterCasted) {
		Monster->InitializeMonster();
		Monster = MonsterCasted;
		UMyGameInstance* GameIns = Cast<UMyGameInstance>(GetGameInstance());
		if (GameIns) {
			GameIns->ActMonster = Monster;
			this->GetPlayerLevel(Character);
			this->StartCombat();
		}
		
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
		//=========(HERE)==========Update the HUD
		GetWorldTimerManager().ClearTimer(CombatTimer);
		DestroyDices();
		Plane->SetVisibility(false, true);
		Monster->GetMesh()->PlayAnimation(Monster->AnimDead, false);
		//=====(HERE) SET VISIBILITY OF THE MONSTER HEALTH BAR
		FLatentActionInfo info;
		UKismetSystemLibrary::Delay(GetWorld(),3.f,info);
		Character->Exp = UKismetMathLibrary::Clamp(Monster->Reward + Character->Exp, 0, Character->MaxExp);
		MonsterSpawned->SetChildActorClass(nullptr);
	}
	else {
		if (GM->Results.Num() == ExpectedDices) {
			Character->Health = Character->Health + *GM->Results.Find(EDiceType::Poison);
			ARogueCharacter* Rogue = Cast<ARogueCharacter>(Character);
			if (Rogue && Rogue->BackStabActivated) {
				Monster->Live = Monster->Live - (2*(*GM->Results.Find(EDiceType::Player)) + *GM->Results.Find(EDiceType::Curse));
				Rogue->BackStabActivated=false;
			}
			else {
				Monster->Live = Monster->Live - (*GM->Results.Find(EDiceType::Player) + *GM->Results.Find(EDiceType::Curse));
			}
			Monster->UpdateMonsterState();
			if (Monster->IsDead || Monster->Live <= 0) {
				CombatEnded = true;
				Character->isInCombat = false;
				//=========(HERE)==========Update the HUD
				GetWorldTimerManager().ClearTimer(CombatTimer);
				DestroyDices();
				Plane->SetVisibility(false, true);
				Monster->GetMesh()->PlayAnimation(Monster->AnimDead, false);
				//=====(HERE) SET VISIBILITY OF THE MONSTER HEALTH BAR
				FLatentActionInfo info;
				UKismetSystemLibrary::Delay(GetWorld(), 3.f, info);
				Character->Exp = UKismetMathLibrary::Clamp(Monster->Reward + Character->Exp, 0, Character->MaxExp);
				MonsterSpawned->SetChildActorClass(nullptr);
			}
			else {
				if (Monster->IsMonsterFrozen) {
					GM->Results.Empty(ExpectedDices);
					//=========UPDATE CHARACTER HUD
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
							//=========UPDATE CHARACTER HUD
							DestroyDices();
							break;
						case EAttackState::CurseAttack:
							Character->States.Add(ENegativeState::Cursed);
							Character->TakeDamageCpp(Monster->Damage);
							GM->Results.Empty(ExpectedDices);
							//=========UPDATE CHARACTER HUD
							DestroyDices();
							break;
						case EAttackState::BlindAttack:
							Character->States.Add(ENegativeState::Blinded);
							Character->TakeDamageCpp(Monster->Damage);
							GM->Results.Empty(ExpectedDices);
							//=========UPDATE CHARACTER HUD
							DestroyDices();
							break;
						case EAttackState::WeaknessAttack:
							Character->Exp--;
							Character->TakeDamageCpp(Monster->Damage);
							GM->Results.Empty(ExpectedDices);
							//=========UPDATE CHARACTER HUD
							DestroyDices();
							break;
						case EAttackState::NoArmorAttack:
							Character->TakeDamageCpp(Monster->Damage);
							GM->Results.Empty(ExpectedDices);
							//=========UPDATE CHARACTER HUD
							DestroyDices();
							break;
						case EAttackState::NoneStateAttack:
							Character->TakeDamageCpp(Monster->Damage);
							GM->Results.Empty(ExpectedDices);
							//=========UPDATE CHARACTER HUD
							DestroyDices();
							break;
						}
					}
					else {
						GM->Results.Empty(ExpectedDices);
						//=========UPDATE CHARACTER HUD
						DestroyDices();
					}
				}
			}
		}
	}
}

void AMonsterRoom::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor);
	if (Player) {
		Character = Player;
		ARogueCharacter* Rogue = Cast<ARogueCharacter>(Character);
		if (Rogue) {
			if (Rogue->EvasionActivated) {
				this->EventFinishRoom();
				Rogue->EvasionActivated = false;
			}else {
				this->RoomBehavior();
				Character->isInCombat = true;
				//=======================Update the HUD
				GetWorldTimerManager().SetTimer(Timer,this, &AMonsterRoom::Check,0.3f,true);
			}
		}else {
			this->RoomBehavior();
			Character->isInCombat = true;
			//=======================Update the HUD
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
	auto PlayerDiceClass = ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/PlayerDice.PlayerDice'"));
	if (PlayerDiceClass.Succeeded()) {
		UGameplayStatics::GetAllActorsOfClass(GetWorld(),PlayerDiceClass.Class, playerDices);
	}
	if (playerDices.Num() != 0) {
		for (int i = 0; i < playerDices.Num(); i++) {
			playerDices[i]->Destroy();
		}
	}
	TArray<AActor*> dungeonDices;
	auto DungeonDiceClass= ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/DungeonDice.DungeonDice''"));
	if (DungeonDiceClass.Succeeded()) {
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), DungeonDiceClass.Class, dungeonDices);
	}
	if (dungeonDices.Num() != 0) {
		for (int j = 0; j < dungeonDices.Num(); j++) {
			dungeonDices[j]->Destroy();
		}
	}
	TArray<AActor*> poisonDices;
	auto PoisonDiceClass= ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/PoisonDice.PoisonDice'"));
	if (PoisonDiceClass.Succeeded()) {
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), PoisonDiceClass.Class, poisonDices);
	}
	if (poisonDices.Num() != 0) {
		for (int k = 0; k < poisonDices.Num(); k++) {
			poisonDices[k]->Destroy();
		}
	}
	TArray<AActor*> curseDices;
	auto CurseDiceClass= ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/CurseDice.CurseDice'"));
	if (CurseDiceClass.Succeeded()) {
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), CurseDiceClass.Class, curseDices);
	}
	if (curseDices.Num() != 0) {
		for (int w = 0; w < curseDices.Num(); w++) {
			curseDices[w]->Destroy();
		}
	}
	Plane->SetVisibility(true, true);
	Controller->bEnableClickEvents = true;
	
}

void AMonsterRoom::LaunchDices()
{
	Plane->SetVisibility(false, true);
	Controller->bEnableClickEvents = false;
	auto PlayerDiceClass = ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/PlayerDice.PlayerDice'"));
	if (PlayerDiceClass.Succeeded()) {
		for (int i = 0; i < PlayerLevel - 1; i++) {
			FVector Loc = FVector(DiceRespawn->GetRelativeLocation().X, DiceRespawn->GetRelativeLocation().Y+(i*-50), DiceRespawn->GetRelativeLocation().Z);
			FRotator Rot = FRotator(UKismetMathLibrary::RandomFloatInRange(0.f,360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f));
			GetWorld()->SpawnActor<AActor>(PlayerDiceClass.Class, Loc, Rot);
		}
	}
	auto DungeonDiceClass = ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/DungeonDice.DungeonDice'"));
	if (DungeonDiceClass.Succeeded()) {
			FVector Loc = FVector(DiceRespawn->GetRelativeLocation().X, DiceRespawn->GetRelativeLocation().Y + 100, DiceRespawn->GetRelativeLocation().Z);
			FRotator Rot = FRotator(UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f));
			GetWorld()->SpawnActor<AActor>(DungeonDiceClass.Class, Loc, Rot);
	}
	if (Character->States.Contains(ENegativeState::Poisoned)) {
		auto PoisonDiceClass = ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/PoisonDice.PoisonDice'"));
		if (PoisonDiceClass.Succeeded()) {
			FVector Loc = FVector(DiceRespawn->GetRelativeLocation().X, DiceRespawn->GetRelativeLocation().Y + 200, DiceRespawn->GetRelativeLocation().Z);
			FRotator Rot = FRotator(UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f));
			GetWorld()->SpawnActor<AActor>(PoisonDiceClass.Class, Loc, Rot);
		}
	}
	if(Character->States.Contains(ENegativeState::Cursed)){
		auto CurseDiceClass = ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/CurseDice.CurseDice'"));
		if (CurseDiceClass.Succeeded()) {
			FVector Loc = FVector(DiceRespawn->GetRelativeLocation().X, DiceRespawn->GetRelativeLocation().Y + 300, DiceRespawn->GetRelativeLocation().Z);
			FRotator Rot = FRotator(UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f), UKismetMathLibrary::RandomFloatInRange(0.f, 360.f));
			GetWorld()->SpawnActor<AActor>(CurseDiceClass.Class, Loc, Rot);
		}
	}
}
