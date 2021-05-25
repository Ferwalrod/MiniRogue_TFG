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
#include "MiniRogue_TFG/Widgets/TombMessage.h"
#include "MiniRogue_TFG/HolyPotion.h"
#include "MiniRogue_TFG/PotionObject.h"

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
	Message = CreateDefaultSubobject<UWidgetComponent>("Message");
	Message->SetupAttachment(GetRootComponent());
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
	LaunchDicesForSearch();
}

void ATombRoom::OnClickedCombatButton(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	LaunchDicesForCombat();
}

void ATombRoom::Check()
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
	if (CombatEnded || FinishedRoom) {
		GetWorldTimerManager().ClearTimer(CheckTimer);
		this->EventFinishRoom();
	}
}

void ATombRoom::WaitForSearchResults()
{
	if (GM->Results.Num() == 2) {
		GetWorldTimerManager().ClearTimer(SearchTimer);
		FLatentActionInfo info;
		info.Linkage = 0;
		info.CallbackTarget = this;
		UKismetSystemLibrary::Delay(GetWorld(), 1.f, info);
		if (Character->PositiveStates.Contains(EPositiveState::Perceptive)) {
			Character->PositiveStates.Remove(Character->PositiveStates.FindId(EPositiveState::Perceptive));
			IsSuccess = true;
		}
		else {
			TArray<AActor*> playerDices;
			//auto PlayerDiceClass = ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/PlayerDice.PlayerDice'"));
			if (PlayerDiceClass) {
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerDiceClass, playerDices);
			}
			if (playerDices.Num() != 0) {
				for (int i = 0; i < playerDices.Num(); i++) {
					ADice* Dice = Cast<ADice>(playerDices[i]);
					if (Dice) {
						if (*Dice->ValueMapping.Find(Dice->FaceShowing) >= 5) {
							IsSuccess = true;
							break;
						}
					}
				}
			}
		}
		if (IsSuccess) {
			TArray<AActor*> dungeonDices;
			//auto DungeonDiceClass= ConstructorHelpers::FClassFinder<AActor>(TEXT("Blueprint'/Game/Blueprints/Dices/DungeonDice.DungeonDice''"));
			if (DungeonDiceClass) {
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), DungeonDiceClass, dungeonDices);
			}
			if (dungeonDices.Num() != 0) {
				ADice* DungeonDice = Cast<ADice>(dungeonDices[0]);
				if (DungeonDice) {
					UTombMessage* TombMessage = Cast<UTombMessage>(Message->GetUserWidgetObject());
					switch (*DungeonDice->ValueMapping.Find(DungeonDice->FaceShowing)) {
					case 1:
						if (Character->Potions.Num() < 2 && !Character->Potions.Contains(AHolyPotion::StaticClass())) {
							Character->Potions.Add(AHolyPotion::StaticClass());
							Message->SetVisibility(true, true);
							if (TombMessage) {
								TombMessage->Message_Text = FText::FromString("+1 Holy Water");
							}
							UKismetSystemLibrary::Delay(GetWorld(), 2.f, info);
							Message->SetVisibility(false, true);
							EventFinishRoom();
							Controller->bEnableClickEvents = true;
							DestroyDicesForSearch();
							GM->Results.Empty();
							Character->UpdateUserInterface();
						}
						break;
					case 2:
						Character->Food = UKismetMathLibrary::Clamp(Character->Food++, 0, Character->MaxFood);
						Message->SetVisibility(true, true);
						if (TombMessage) {
							TombMessage->Message_Text = FText::FromString("+1 Food");
						}
						UKismetSystemLibrary::Delay(GetWorld(), 2.f, info);
						Message->SetVisibility(false, true);
						EventFinishRoom();
						Controller->bEnableClickEvents = true;
						DestroyDicesForSearch();
						GM->Results.Empty();
						Character->UpdateUserInterface();
						break;
					case 3:
						Character->Gold = UKismetMathLibrary::Clamp(Character->Gold++, 0, Character->MaxGold);
						Message->SetVisibility(true, true);
						if (TombMessage) {
							TombMessage->Message_Text = FText::FromString("+1 Gold");
						}
						UKismetSystemLibrary::Delay(GetWorld(), 2.f, info);
						Message->SetVisibility(false, true);
						EventFinishRoom();
						Controller->bEnableClickEvents = true;
						DestroyDicesForSearch();
						GM->Results.Empty();
						Character->UpdateUserInterface();
						break;
					case 4:
						Character->Exp = UKismetMathLibrary::Clamp(Character->Exp++, 0, Character->MaxGold);
						Message->SetVisibility(true, true);
						if (TombMessage) {
							TombMessage->Message_Text = FText::FromString("+1 Experience");
						}
						UKismetSystemLibrary::Delay(GetWorld(), 2.f, info);
						Message->SetVisibility(false, true);
						EventFinishRoom();
						Controller->bEnableClickEvents = true;
						DestroyDicesForSearch();
						GM->Results.Empty();
						Character->UpdateUserInterface();
						break;
					case 5:
						Character->Food = UKismetMathLibrary::Clamp(Character->Food--, 0, Character->MaxFood);
						Message->SetVisibility(true, true);
						if (TombMessage) {
							TombMessage->Message_Text = FText::FromString("-1 Food");
						}
						UKismetSystemLibrary::Delay(GetWorld(), 2.f, info);
						Message->SetVisibility(false, true);
						EventFinishRoom();
						Controller->bEnableClickEvents = true;
						DestroyDicesForSearch();
						GM->Results.Empty();
						Character->UpdateUserInterface();
						break;
					case 6:
						StartCombat();
						Message->SetVisibility(true, true);
						if (TombMessage) {
							TombMessage->Message_Text = FText::FromString("Ghost appeared");
						}
						UKismetSystemLibrary::Delay(GetWorld(), 2.f, info);
						Message->SetVisibility(false, true);
						DestroyDicesForSearch();
						GM->Results.Empty(ExpectedDices);
						Character->UpdateUserInterface();
						break;
					}

				}
			}

		}
		else {
			FinishedRoom = true;
			Controller->bEnableClickEvents = true;
			Message->SetVisibility(true, true);
			UTombMessage* TombMessage = Cast<UTombMessage>(Message->GetUserWidgetObject());
			if (TombMessage) {
				TombMessage->Message_Text=FText::FromString("Better luck next time");
			}
			FLatentActionInfo info7;
			UKismetSystemLibrary::Delay(GetWorld(), 2.f, info7);
			Message->SetVisibility(false, true);
			DestroyDicesForSearch();
			GM->Results.Empty();
			Character->UpdateUserInterface();
		}
	}
}

void ATombRoom::StartCombat()
{
	Text1->SetVisibility(true, true);
	Combat_Button->SetVisibility(true, true);
	MonsterSpawned->SetChildActorClass(MonsterClass);
	MonsterSpawned->CreateChildActor();
	AMonsterBase* MonsterCasted = Cast<AMonsterBase>(MonsterSpawned->GetChildActor());
	if (MonsterCasted) {
		MonsterCasted->InitializeMonster();
		Monster = MonsterCasted;


		GI->ActMonster = MonsterCasted;
		this->GetPlayerLevel(Character);
	}
	GetWorldTimerManager().SetTimer(CombatTimer, this, &ATombRoom::PlayerTurn, 0.4f, true);

}

void ATombRoom::PlayerTurn()
{
	if (Monster->IsDead) {
		CombatEnded = true;
		Character->isInCombat = false;
		Character->UpdateUserInterface();
		GetWorldTimerManager().ClearTimer(CombatTimer);
		DestroyDicesForCombat();
		Combat_Button->SetVisibility(false, true);
		Monster->GetMesh()->PlayAnimation(Monster->AnimDead, false);
		//=====(HERE) SET VISIBILITY OF THE MONSTER HEALTH BAR
		FLatentActionInfo info8;
		UKismetSystemLibrary::Delay(GetWorld(), 3.f, info8);
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
				Monster->Live = Monster->Live - (2 * (*GM->Results.Find(EDiceType::Player)) + curse);
				Rogue1->BackStabActivated = false;
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
				DestroyDicesForCombat();
				Combat_Button->SetVisibility(false, true);
				Monster->GetMesh()->PlayAnimation(Monster->AnimDead, false);
				//=====(HERE) SET VISIBILITY OF THE MONSTER HEALTH BAR
				FLatentActionInfo info9;
				UKismetSystemLibrary::Delay(GetWorld(), 3.f, info9);
				Character->Exp = UKismetMathLibrary::Clamp(Monster->Reward + Character->Exp, 0, Character->MaxExp);
				MonsterSpawned->SetChildActorClass(nullptr);
				MonsterSpawned->CreateChildActor();
			}
			else {
				if (Monster->IsMonsterFrozen) {
					GM->Results.Empty(ExpectedDices);
					Character->UpdateUserInterface();
					Monster->IsMonsterFrozen = false;
					DestroyDicesForCombat();
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
							DestroyDicesForCombat();
							break;
						case EAttackState::CurseAttack:
							Character->States.Add(ENegativeState::Cursed);
							Character->TakeDamageCpp(Monster->Damage);
							GM->Results.Empty(ExpectedDices);
							Character->UpdateUserInterface();
							DestroyDicesForCombat();
							break;
						case EAttackState::BlindAttack:
							Character->States.Add(ENegativeState::Blinded);
							Character->TakeDamageCpp(Monster->Damage);
							GM->Results.Empty(ExpectedDices);
							Character->UpdateUserInterface();
							DestroyDicesForCombat();
							break;
						case EAttackState::WeaknessAttack:
							Character->Exp--;
							Character->TakeDamageCpp(Monster->Damage);
							GM->Results.Empty(ExpectedDices);
							Character->UpdateUserInterface();
							DestroyDicesForCombat();
							break;
						case EAttackState::NoArmorAttack:
							Character->TakeDamageCpp(Monster->Damage);
							GM->Results.Empty(ExpectedDices);
							Character->UpdateUserInterface();
							DestroyDicesForCombat();
							break;
						case EAttackState::NoneStateAttack:
							Character->TakeDamageCpp(Monster->Damage);
							GM->Results.Empty(ExpectedDices);
							Character->UpdateUserInterface();
							DestroyDicesForCombat();
							break;
						}
					}
					else {
						GM->Results.Empty(ExpectedDices);
						Character->UpdateUserInterface();
						DestroyDicesForCombat();
					}
				}
			}
		}
	}
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
