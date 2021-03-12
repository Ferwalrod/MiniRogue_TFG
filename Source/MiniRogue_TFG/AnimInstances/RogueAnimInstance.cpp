// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueAnimInstance.h"
//#include "Kismet/KismetMathLibrary.h"
//#include "Kismet/KismetSystemLibrary.h"

URogueAnimInstance::URogueAnimInstance() {

	isMoving = false;
}

void URogueAnimInstance::NativeUpdateAnimation(float DeltaTime) {

	Super::NativeUpdateAnimation(DeltaTime);

	APawn* PawnPlayer = this->TryGetPawnOwner();
	if (PawnPlayer != nullptr) {
		float velocity = PawnPlayer->GetVelocity().Size();
		isMoving = velocity > 0.;
	}
}