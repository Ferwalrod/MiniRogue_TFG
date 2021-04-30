// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniRogue_TFG/Rooms/BaseRoom.h"
#include "BossRoom.generated.h"

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
class UBoxComponent;

UCLASS()
class MINIROGUE_TFG_API ABossRoom : public ABaseRoom
{
	GENERATED_BODY()

public:
	ABossRoom();
	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UChildActorComponent* MonsterSpawned;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USphereComponent* DiceRespawn;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Plane;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UTextRenderComponent* Text;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UBoxComponent* Ladders;

	//Attributes
	FTimerHandle CombatTimer;
	FTimerHandle Timer;

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
		bool IsFinalLevel;

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
	virtual void RoomBehavior() override;
	void GetPlayerLevel(ABaseCharacter* Player);
	void StartCombat();
	void Check();
	void PlayerTurn();
	void NextLevel();

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnLaddersOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnClickedButton(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
	//Macros
	void DestroyDices();
	void LaunchDices();
	
};