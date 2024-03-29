// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DiceType.h"
#include "GameFramework/GameModeBase.h"
#include "MiniRogue_TFGGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MINIROGUE_TFG_API AMiniRogue_TFGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Temporal")
	TMap<TEnumAsByte<EDiceType>,int> Results;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Temporal")
	bool RoomFinished;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Temporal")
	FVector RightDoor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Temporal")
	FVector BottomDoor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Temporal")
	FVector	Center;
};
