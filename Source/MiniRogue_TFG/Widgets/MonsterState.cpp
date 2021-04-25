// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterState.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "MiniRogue_TFG/Enumerates/AttackState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Texture2D.h"
#include "MiniRogue_TFG/Characters/MonsterBase.h"



void UMonsterState::NativeConstruct()
{
	
	/*auto picture = ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("Texture2D'/Game/Textures/states/poison_picture.poison_picture'"));
	if (picture.Succeeded()) {
		Poison = picture.Object;
		
	}
	auto picture1 = ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("Texture2D'/Game/Textures/states/curse_picture.curse_picture'"));
	if (picture1.Succeeded()) {
		Curse = picture1.Object;
	}
	auto picture2 = ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("Texture2D'/Game/Textures/states/Blind.Blind'"));
	if (picture2.Succeeded()) {
		Blind = picture2.Object;
	}
	auto picture3 = ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("Texture2D'/Game/Textures/states/Weakness_picture.Weakness_picture'"));
	if (picture3.Succeeded()) {
		Weakness = picture3.Object;
	}
	auto picture4 = ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("Texture2D'/Game/Textures/states/Ignore_armor.Ignore_armor'"));
	if (picture4.Succeeded()) {
		NoArmor = picture4.Object;
	}*/

}

void UMonsterState::NativeTick(const FGeometry& Geometry, float DeltaTime)
{
	if (Monster) {
		ProgressBar_106->SetPercent(GetPercent());
	}
}

FText UMonsterState::GetNameText()
{
	return UKismetTextLibrary::Conv_NameToText(Monster->MonsterName);
}

FText UMonsterState::GetFloorText()
{
	return UKismetTextLibrary::Conv_FloatToText(Monster->Floor,ERoundingMode::HalfFromZero);
}

FText UMonsterState::GetDamageText()
{
	return UKismetTextLibrary::Conv_StringToText(UKismetStringLibrary::Concat_StrStr("Damage:",UKismetStringLibrary::Conv_FloatToString(Monster->Damage)));
}

float UMonsterState::GetPercent()
{
	float live = Monster->Live;
	float MaxLive = Monster->MaxMonsterLive;
	return live / MaxLive;
}

void UMonsterState::SetMonsterOwner(AMonsterBase* Owner)
{
	Monster = Owner;
	switch (Monster->DamageType) {
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
	case EAttackState::BlindAttack:
		if (Blind) {
			DamageTexture = Blind;
		}
		break;
	case EAttackState::WeaknessAttack:
		if (Weakness) {
			DamageTexture = Weakness;
		}
		break;
	case EAttackState::NoArmorAttack:
		if (NoArmor) {
			DamageTexture = NoArmor;
		}
		break;
	case EAttackState::NoneStateAttack:
		damage_type->SetOpacity(0.f);
		break;
	}
	FLatentActionInfo info=FLatentActionInfo();
	UKismetSystemLibrary::Delay(GetWorld(), 0.01f,info);
	damage_type->SetBrushSize(FVector2D(44.f, 44.f));
	
	Name_Text->SetText(GetNameText());
	Floor->SetText(GetFloorText());
	Damage_text->SetText(GetDamageText());

}
