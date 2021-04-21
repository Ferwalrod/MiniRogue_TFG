// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MiniRogue_TFG/Enumerates/AttackState.h"
#include "MiniRogue_TFG/Enumerates/NegativeState.h"
#include "MiniRogue_TFG/Structs/MonsterLevelStruct.h"
#include "MonsterBase.generated.h"

class UWidgetComponent;
class USkeletalMesh;
class UAnimSequence;

UCLASS()
class MINIROGUE_TFG_API AMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterBase();
	//Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
	TArray<FMonsterLevelStruct> MonsterLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
	int Live;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
	int Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
	TEnumAsByte<EAttackState> DamageType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
	int Reward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
	FName MonsterName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
	TSet<TEnumAsByte<ENegativeState>> NegativeStates;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
	bool IsDead;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
	int MaxMonsterLive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
	int Floor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
	USkeletalMesh* EnemyMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
	UAnimSequence* AnimIdle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
	UAnimSequence* AnimCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
	UAnimSequence* AnimDead;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
	bool IsMonsterFrozen;

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	UWidgetComponent* HealthBar;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void InitializeMonster();
	UFUNCTION(BlueprintCallable)
	void UpdateMonsterState();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
