// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "InputCoreTypes.h"
#include "MiniRogue_TFG/Enumerates/NegativeState.h"
#include "MiniRogue_TFG/WeaponType.h"
#include "TimerManager.h"
#include "MiniRogue_TFG/Interfaces/Potion.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"


class APotionObject;

UENUM(BlueprintType)
enum EPositiveState {
	Perceptive UMETA(DisplayName = "Perceptive")
};

UCLASS()
class MINIROGUE_TFG_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	//Attributes
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Attributes")
	int Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	int MaxHealth = 20;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int Exp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	int MaxExp=23;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int Food;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	int MaxFood = 4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int Gold;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	int MaxGold = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int Armor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	int MaxArmor = 4;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	int WeaponCharges = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	TArray<APotionObject*> Potions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	TSet<TEnumAsByte<ENegativeState>> States;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	TSet<TEnumAsByte<EPositiveState>> PositiveStates;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	bool RightArrowVisibility = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	bool BottomArrowVisibility = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	bool NextSuccess = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	bool isInCombat = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	TEnumAsByte<EWeaponType> currentWeapon = NoWeapon;

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* RightArrow;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BottomArrow;




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle Timer;

	void CheckArrowVisibilities();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Events of the arrows
	UFUNCTION()
	void OnClickedRightArrow(UPrimitiveComponent* TouchedComponent,FKey buttonPresed);
	UFUNCTION()
	void OnClickedBottomArrow(UPrimitiveComponent* TouchedComponent, FKey buttonPresed);

	void Debug();

	


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
