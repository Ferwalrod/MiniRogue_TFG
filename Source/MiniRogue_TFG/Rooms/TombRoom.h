// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniRogue_TFG/Rooms/BaseRoom.h"
#include "TimerManager.h"
#include "TombRoom.generated.h"

class UStaticMeshComponent;
class UChildActorComponent;
class USphereComponent;
class UTextRenderComponent;
class AMiniRogue_TFGGameModeBase;
class AMonsterBase;
class APlayerController;
class AActor;
class UPrimitiveComponent;
class ADice;
class UWidgetComponent;
class ABaseCharacter;

UCLASS()
class MINIROGUE_TFG_API ATombRoom : public ABaseRoom
{
	GENERATED_BODY()

public:
	ATombRoom();
	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UChildActorComponent* MonsterSpawned;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USphereComponent* DiceRespawn;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Combat_Button;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UTextRenderComponent* Text1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Search_Button;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UTextRenderComponent* Text2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UWidgetComponent* Message;

	//Attributes
	UPROPERTY()
	FTimerHandle CheckTimer;
	UPROPERTY()
	FTimerHandle CombatTimer;
	UPROPERTY()
	FTimerHandle SearchTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		bool CombatEnded;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		AMiniRogue_TFGGameModeBase* GM;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		APlayerController* Controller;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int ExpectedDices;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		AMonsterBase* Monster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		bool Child;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int PlayerLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		TSubclassOf<AMonsterBase> MonsterClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		bool FinishedRoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		bool IsSuccess;


protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dices")
		TSubclassOf<ADice> PlayerDiceClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dices")
		TSubclassOf<ADice> DungeonDiceClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dices")
		TSubclassOf<ADice> PoisonDiceClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dices")
		TSubclassOf<ADice> CurseDiceClass;

public:
	virtual void Tick(float DeltaTime) override;

	//Functions
	virtual void RoomBehavior() override;
	void GetPlayerLevel(ABaseCharacter* Player);
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnClickedSearchButton(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
	UFUNCTION()
		void OnClickedCombatButton(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	//Events
	void Check();
	void WaitForSearchResults();
	void StartCombat();
	void PlayerTurn();

	//Macros
	void LaunchDicesForSearch();
	void DestroyDicesForSearch();
	void LaunchDicesForCombat();
	void DestroyDicesForCombat();
};
