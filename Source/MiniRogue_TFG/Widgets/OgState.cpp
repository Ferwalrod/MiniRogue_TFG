// Fill out your copyright notice in the Description page of Project Settings.


#include "OgState.h"
#include "MiniRogue_TFG/Characters/OgRemains.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "MiniRogue_TFG/Enumerates/AttackState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Texture2D.h"
#include "MiniRogue_TFG/Characters/MonsterBase.h"

void UOgState::NativeConstruct()
{
}

void UOgState::NativeTick(const FGeometry& Geometry, float DeltaTime)
{
	if (Og) {
		ProgressBar_106->SetPercent(GetPercent());
		//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Porcentaje de vida: %f"),(GetPercent())));
	}
}

FText UOgState::GetNameText()
{
	return UKismetTextLibrary::Conv_NameToText(Og->MonsterName);
}

FText UOgState::GetPhaseText()
{
	return UKismetTextLibrary::Conv_FloatToText(Og->PhaseNumber, ERoundingMode::HalfFromZero);
}

FText UOgState::GetDamageText()
{
	return UKismetTextLibrary::Conv_StringToText(UKismetStringLibrary::Concat_StrStr("Damage:", UKismetStringLibrary::Conv_FloatToString(Og->Damage)));
}

float UOgState::GetPercent()
{
	float live = UKismetMathLibrary::Conv_IntToFloat(Og->Live);
	float MaxLive = UKismetMathLibrary::Conv_IntToFloat(Og->MaxMonsterLive);
	return live / MaxLive;
}

void UOgState::SetMonsterOwner(AOgRemains* Owner)
{
	Og = Owner;
	switch (Og->DamageType) {
	case EAttackState::PoisonAttack:
		if (Poison) {
			DamageTexture = Poison;
		}
		break;
	case EAttackState::CurseAttack:
		if (Curse) {
			DamageTexture = Curse;
		}
		break;
	}
	FLatentActionInfo info = FLatentActionInfo();
	UKismetSystemLibrary::Delay(GetWorld(), 0.01f, info);
	damage_type->SetBrushSize(FVector2D(44.f, 44.f));

	Name_Text->SetText(GetNameText());
	Phase->SetText(GetPhaseText());
	Damage_text->SetText(GetDamageText());
	ProgressBar_106->SetPercent(GetPercent());
}

void UOgState::UpdateWidget()
{
	damage_type->SetBrushSize(FVector2D(44.f, 44.f));
	Name_Text->SetText(GetNameText());
	Phase->SetText(GetPhaseText());
	Damage_text->SetText(GetDamageText());
	ProgressBar_106->SetPercent(GetPercent());
}
