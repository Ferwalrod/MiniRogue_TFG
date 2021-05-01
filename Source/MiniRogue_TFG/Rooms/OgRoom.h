// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniRogue_TFG/Rooms/BaseRoom.h"
#include "OgRoom.generated.h"



class UStaticMeshComponent;
class UChildActorComponent;
class USphereComponent;
class UTextRenderComponent;
class AMiniRogue_TFGGameModeBase;
class AMonsterBase;
class AOgRemains;
class APlayerController;
class AActor;
class UPrimitiveComponent;
class ADice;

UCLASS()
class MINIROGUE_TFG_API AOgRoom : public ABaseRoom
{
	GENERATED_BODY()
public:

	AOgRoom();

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
		AOgRemains* FinalBoss;
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
	//Functions
	virtual void Tick(float DeltaTime) override;
	virtual void RoomBehavior() override;
	void GetPlayerLevel(ABaseCharacter* Player);
	void NextLevel();
	void Check();
	void PlayerTurn();
	void StartCombat();


	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnClickedButton(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	UFUNCTION()
		void OnLaddersOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult);

	//Macros
	void DestroyDices();
	void LaunchDices();
	
};
