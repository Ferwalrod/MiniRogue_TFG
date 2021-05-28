// Fill out your copyright notice in the Description page of Project Settings.


#include "Merchant.h"
#include "MiniRogue_TFG/PotionObject.h"
#include "MiniRogue_TFG/FirePotion.h"
#include "MiniRogue_TFG/FrostPotion.h"
#include "MiniRogue_TFG/HolyPotion.h"
#include "MiniRogue_TFG/PoisonPotion.h"
#include "MiniRogue_TFG/PerceptionPotion.h"
#include "MiniRogue_TFG/HealthPotion.h"
#include "MiniRogue_TFG/Characters/BaseCharacter.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"

void UMerchant::NativeConstruct() {

	Super::NativeConstruct();

	ABaseCharacter* Character = Cast<ABaseCharacter>(GetOwningPlayer()->GetPawn());
	if (Character) {
		Player = Character;
		RefreshGold(Player->Gold);
		RefreshFood(Player->Food);
		RefreshArmor(Player->Armor);
		RefreshPotions();
	}
	//On Clicked Sell Option
	Sell_Option1->OnClicked.AddDynamic(this, &UMerchant::OnClicked_Sell_Option1);
	//On Clicked Leave Button
	Leave_Button->OnClicked.AddDynamic(this, &UMerchant::OnClicked_Leave_Button);
	//Buy elements logic on the card
	Option1->OnClicked.AddDynamic(this, &UMerchant::OnClicked_Option1);
	Option2->OnClicked.AddDynamic(this, &UMerchant::OnClicked_Option2);
	Option3->OnClicked.AddDynamic(this, &UMerchant::OnClicked_Option3);
	Option4->OnClicked.AddDynamic(this, &UMerchant::OnClicked_Option4);
	Option5->OnClicked.AddDynamic(this, &UMerchant::OnClicked_Option5);
	//Buy Potions logic
	Buy_Fire_potion_Button->OnClicked.AddDynamic(this, &UMerchant::OnClicked_Buy_Fire_potion_Button);
	Buy_Frost_potion_Button->OnClicked.AddDynamic(this, &UMerchant::OnClicked_Buy_Frost_potion_Button);
	Buy_Holy_potion_Button->OnClicked.AddDynamic(this, &UMerchant::OnClicked_Buy_Holy_potion_Button);
	Buy_Health_potion_Button->OnClicked.AddDynamic(this, &UMerchant::OnClicked_Buy_Health_potion_Button);
	Buy_Perception_potion_Button->OnClicked.AddDynamic(this, &UMerchant::OnClicked_Buy_Perception_potion_Button);
	Buy_Poison_potion_Button->OnClicked.AddDynamic(this, &UMerchant::OnClicked_Buy_Poison_potion_Button);
	//Sell Potions logic
	Sell_Fire_potion_Button->OnClicked.AddDynamic(this, &UMerchant::OnClicked_Sell_Fire_potion_Button);
	Sell_Frost_potion_Button->OnClicked.AddDynamic(this, &UMerchant::OnClicked_Sell_Frost_potion_Button);
	Sell_Health_potion_Button->OnClicked.AddDynamic(this, &UMerchant::OnClicked_Sell_Health_potion_Button);
	Sell_Holy_potion_Button->OnClicked.AddDynamic(this, &UMerchant::OnClicked_Sell_Holy_potion_Button);
	Sell_Perception_potion_Button->OnClicked.AddDynamic(this, &UMerchant::OnClicked_Sell_Perception_potion_Button);
	Sell_Poison_potion_Button->OnClicked.AddDynamic(this, &UMerchant::OnClicked_Sell_Poison_potion_Button);
	//Hover logic
	// Un/hover over the buy elements of the card
	Option1->OnHovered.AddDynamic(this, &UMerchant::OnHovered_Option1);
	Option1->OnUnhovered.AddDynamic(this, &UMerchant::OnUnhovered_Option1);
	Option2->OnHovered.AddDynamic(this, &UMerchant::OnHovered_Option2);
	Option2->OnUnhovered.AddDynamic(this, &UMerchant::OnUnhovered_Option2);
	Option3->OnHovered.AddDynamic(this, &UMerchant::OnHovered_Option3);
	Option3->OnUnhovered.AddDynamic(this, &UMerchant::OnUnhovered_Option3);
	Option4->OnHovered.AddDynamic(this, &UMerchant::OnHovered_Option4);
	Option4->OnUnhovered.AddDynamic(this, &UMerchant::OnUnhovered_Option4);
	Option5->OnHovered.AddDynamic(this, &UMerchant::OnHovered_Option5);
	Option5->OnUnhovered.AddDynamic(this, &UMerchant::OnUnhovered_Option5);
	//Un/hover over the sell elements of the card
	Sell_Option1->OnHovered.AddDynamic(this, &UMerchant::OnHovered_Sell_Option1);
	Sell_Option1->OnUnhovered.AddDynamic(this, &UMerchant::OnUnhovered_Sell_Option1);
	//Un/hover over the buy potions
	Buy_Fire_potion_Button->OnHovered.AddDynamic(this, &UMerchant::OnHovered_Buy_Fire_potion_Button);
	Buy_Fire_potion_Button->OnUnhovered.AddDynamic(this, &UMerchant::OnUnhovered_Buy_Fire_potion_Button);
	Buy_Frost_potion_Button->OnHovered.AddDynamic(this, &UMerchant::OnHovered_Buy_Frost_potion_Button);
	Buy_Frost_potion_Button->OnUnhovered.AddDynamic(this, &UMerchant::OnUnhovered_Buy_Frost_potion_Button);
	Buy_Health_potion_Button->OnHovered.AddDynamic(this, &UMerchant::OnHovered_Buy_Health_potion_Button);
	Buy_Health_potion_Button->OnUnhovered.AddDynamic(this, &UMerchant::OnUnhovered_Buy_Health_potion_Button);
	Buy_Holy_potion_Button->OnHovered.AddDynamic(this, &UMerchant::OnHovered_Buy_Holy_potion_Button);
	Buy_Holy_potion_Button->OnUnhovered.AddDynamic(this, &UMerchant::OnUnhovered_Buy_Holy_potion_Button);
	Buy_Perception_potion_Button->OnHovered.AddDynamic(this, &UMerchant::OnHovered_Buy_Perception_potion_Button);
	Buy_Perception_potion_Button->OnUnhovered.AddDynamic(this, &UMerchant::OnUnhovered_Buy_Perception_potion_Button);
	Buy_Poison_potion_Button->OnHovered.AddDynamic(this, &UMerchant::OnHovered_Buy_Poison_potion_Button);
	Buy_Poison_potion_Button->OnUnhovered.AddDynamic(this, &UMerchant::OnUnhovered_Buy_Poison_potion_Button);
	//Un/hover over the Sell potions
	Sell_Fire_potion_Button->OnHovered.AddDynamic(this, &UMerchant::OnHovered_Sell_Fire_potion_Button);
	Sell_Fire_potion_Button->OnUnhovered.AddDynamic(this, &UMerchant::OnUnhovered_Sell_Fire_potion_Button);
	Sell_Frost_potion_Button->OnHovered.AddDynamic(this, &UMerchant::OnHovered_Sell_Frost_potion_Button);
	Sell_Frost_potion_Button->OnUnhovered.AddDynamic(this, &UMerchant::OnUnhovered_Sell_Frost_potion_Button);
	Sell_Health_potion_Button->OnHovered.AddDynamic(this, &UMerchant::OnHovered_Sell_Health_potion_Button);
	Sell_Health_potion_Button->OnUnhovered.AddDynamic(this, &UMerchant::OnUnhovered_Sell_Health_potion_Button);
	Sell_Holy_potion_Button->OnHovered.AddDynamic(this, &UMerchant::OnHovered_Sell_Holy_potion_Button);
	Sell_Holy_potion_Button->OnUnhovered.AddDynamic(this, &UMerchant::OnUnhovered_Sell_Holy_potion_Button);
	Sell_Perception_potion_Button->OnHovered.AddDynamic(this, &UMerchant::OnHovered_Sell_Perception_potion_Button);
	Sell_Perception_potion_Button->OnUnhovered.AddDynamic(this, &UMerchant::OnUnhovered_Sell_Perception_potion_Button);
	Sell_Poison_potion_Button->OnHovered.AddDynamic(this, &UMerchant::OnHovered_Sell_Poison_potion_Button);
	Sell_Poison_potion_Button->OnUnhovered.AddDynamic(this, &UMerchant::OnUnhovered_Sell_Poison_potion_Button);

	DescriptionTexts.Init(FText::FromString(""), 24);
	DescriptionTexts[0] = FText::FromString("Recupera 1 de vida por 1 de oro");
	DescriptionTexts[1] = FText::FromString("Compra 1 de comida por 2 de oro");
	DescriptionTexts[2] = FText::FromString("Cura todos tus estados por 2 de oro");
	DescriptionTexts[3] = FText::FromString("Recupera 4 de vida por 3 de oro");
	DescriptionTexts[4] = FText::FromString("Compra 1 de armadura por 5 de oro");
	DescriptionTexts[5] = FText::FromString("Vende 1 de armadura por 3 de oro");
	DescriptionTexts[6] = FText::FromString("Compra una pocion de fuego por 5 de oro ");
	DescriptionTexts[7] = FText::FromString("Compra una pocion de hielo por 5 de oro ");
	DescriptionTexts[8] = FText::FromString("Compra una pocion de salud por 5 de oro ");
	DescriptionTexts[9] = FText::FromString("Compra una pocion de agua bendita por 5 de oro");
	DescriptionTexts[10] = FText::FromString("Compra una pocion de percepcion por 5 de oro ");
	DescriptionTexts[11] = FText::FromString("Compra una pocion de veneno por 5 de oro ");
	DescriptionTexts[12] = FText::FromString("Vende una pocion de fuego por 3 de oro");
	DescriptionTexts[13] = FText::FromString("Vende una pocion de hielo por 3 de oro");
	DescriptionTexts[14] = FText::FromString("Vende una pocion de salud por 3 de oro ");
	DescriptionTexts[15] = FText::FromString("Vende una pocion de agua bendita por 3 de oro");
	DescriptionTexts[16] = FText::FromString("Vende una pocion de percepcion por 3 de oro ");
	DescriptionTexts[17] = FText::FromString("Vende una pocion de veneno por 3 de oro ");
	DescriptionTexts[18] = FText::FromString("No tienes suficiente oro");
	DescriptionTexts[19] = FText::FromString("No tienes armadura para vender");
	DescriptionTexts[20] = FText::FromString("Tienes el máximo de pociones permitidas");
	DescriptionTexts[21] = FText::FromString("Ya tienes esa pocion");
	DescriptionTexts[22] = FText::FromString("No tienes esa pocion");
	DescriptionTexts[23] = FText::FromString("Ya tienes la maxima cantidad de oro");

}
void UMerchant::NativeTick(const FGeometry& Geometry, float DeltaTime)
{
	Super::NativeTick(Geometry, DeltaTime);
}

void UMerchant::RefreshGold(int Gold)
{
	GoldAmount = UKismetTextLibrary::Conv_StringToText(UKismetStringLibrary::Concat_StrStr("Gold:",UKismetStringLibrary::Conv_IntToString(Gold)));
}

void UMerchant::RefreshFood(int Food)
{
	FoodAmount= UKismetTextLibrary::Conv_StringToText(UKismetStringLibrary::Concat_StrStr("Food:", UKismetStringLibrary::Conv_IntToString(Food)));
}

void UMerchant::RefreshArmor(int Armor)
{
	ArmorAmount= UKismetTextLibrary::Conv_StringToText(UKismetStringLibrary::Concat_StrStr("Armor:", UKismetStringLibrary::Conv_IntToString(Armor)));
}

void UMerchant::RefreshPotions()
{
	if (Player->Potions.Contains(AFirePotion::StaticClass())) {
		Fire_potion_amount->SetText(UKismetTextLibrary::Conv_StringToText("1"));
	}
	else {
		Fire_potion_amount->SetText(UKismetTextLibrary::Conv_StringToText("0"));
	}
	if (Player->Potions.Contains(AFrostPotion::StaticClass())) {
		Frost_potion_amount->SetText(UKismetTextLibrary::Conv_StringToText("1"));
	}
	else {
		Frost_potion_amount->SetText(UKismetTextLibrary::Conv_StringToText("0"));
	}
	if (Player->Potions.Contains(APoisonPotion::StaticClass())) {
		Poison_potion_amount->SetText(UKismetTextLibrary::Conv_StringToText("1"));
	}
	else {
		Poison_potion_amount->SetText(UKismetTextLibrary::Conv_StringToText("0"));
	}
	if (Player->Potions.Contains(AHealthPotion::StaticClass())) {
		Health_potion_amount->SetText(UKismetTextLibrary::Conv_StringToText("1"));
	}
	else {
		Health_potion_amount->SetText(UKismetTextLibrary::Conv_StringToText("0"));
	}
	if (Player->Potions.Contains(AHolyPotion::StaticClass())) {
		Sacred_potion_amount->SetText(UKismetTextLibrary::Conv_StringToText("1"));
	}
	else {
		Sacred_potion_amount->SetText(UKismetTextLibrary::Conv_StringToText("0"));
	}
	if (Player->Potions.Contains(APerceptionPotion::StaticClass())) {
		Perception_potion_amount->SetText(UKismetTextLibrary::Conv_StringToText("1"));
	}
	else {
		Perception_potion_amount->SetText(UKismetTextLibrary::Conv_StringToText("0"));
	}
}

void UMerchant::OnClicked_Sell_Option1()
{
	if (Player->Armor < 1) {
		DescriptionText = DescriptionTexts[19];
		FLatentActionInfo info;
		info.Linkage = 0;
		info.CallbackTarget = this;
		UKismetSystemLibrary::Delay(GetWorld(), 2.f, info);
		DescriptionText = UKismetTextLibrary::Conv_StringToText("");
	}
	else {
		Player->Armor--;
		RefreshArmor(Player->Armor);
		Player->Gold = Player->Gold + 3;
		if (Player->Gold > Player->MaxGold) {
			Player->Gold = Player->MaxGold;
			RefreshGold(Player->Gold);
		}
		else {
			RefreshGold(Player->Gold);
		}

		Player->UpdateUserInterface();
	}
}

void UMerchant::OnClicked_Leave_Button()
{
	CommerceFinished = true;
	this->RemoveFromParent();
}

void UMerchant::OnClicked_Option1()
{
	if (Player->Gold == 0) {
		DescriptionText = DescriptionTexts[18];
		FLatentActionInfo info;
		info.Linkage = 0;
		info.CallbackTarget = this;
		UKismetSystemLibrary::Delay(GetWorld(), 2.f, info);
		DescriptionText = UKismetTextLibrary::Conv_StringToText("");
	}
	else {
		Player->Health++;
		if (Player->Health > Player->MaxHealth) {
			Player->Health = Player->MaxHealth;
			Player->Gold--;
			RefreshGold(Player->Gold);
		}
		else {
			Player->Gold--;
			RefreshGold(Player->Gold);
		}
	}

	Player->UpdateUserInterface();
}

void UMerchant::OnClicked_Option2()
{
	if (Player->Gold < 2) {
		DescriptionText = DescriptionTexts[18];
		FLatentActionInfo info;
		info.Linkage = 0;
		info.CallbackTarget = this;
		UKismetSystemLibrary::Delay(GetWorld(), 2.f, info);
		DescriptionText = UKismetTextLibrary::Conv_StringToText("");
	}
	else {
		Player->Food++;
		Player->Gold = Player->Gold - 2;
		if (Player->Food > Player->MaxFood) {
			Player->Food = Player->MaxFood;
			RefreshGold(Player->Gold);
			RefreshFood(Player->Food);
		}
		else {
			RefreshGold(Player->Gold);
			RefreshFood(Player->Food);
		}
	}
}

void UMerchant::OnClicked_Option3()
{
	if (Player->Gold < 2) {
		DescriptionText = DescriptionTexts[18];
		FLatentActionInfo info;
		info.Linkage = 0;
		info.CallbackTarget = this;
		UKismetSystemLibrary::Delay(GetWorld(), 2.f, info);
		DescriptionText = UKismetTextLibrary::Conv_StringToText("");
	}
	else {
		Player->States.Empty(3);
		Player->Gold = Player->Gold - 2;
		RefreshGold(Player->Gold);
	}
}

void UMerchant::OnClicked_Option4()
{
	if (Player->Gold < 3) {
		DescriptionText = DescriptionTexts[18];
		FLatentActionInfo info;
		info.Linkage = 0;
		info.CallbackTarget = this;
		UKismetSystemLibrary::Delay(GetWorld(), 2.f, info);
		DescriptionText = UKismetTextLibrary::Conv_StringToText("");
	}
	else {
		Player->Gold = Player->Gold - 3;
		RefreshGold(Player->Gold);
		Player->Health = UKismetMathLibrary::Clamp(Player->Health + 4, 0, Player->MaxHealth);
	}
}

void UMerchant::OnClicked_Option5()
{
	if (Player->Gold < 5) {
		DescriptionText = DescriptionTexts[18];
		FLatentActionInfo info;
		info.Linkage = 0;
		info.CallbackTarget = this;
		UKismetSystemLibrary::Delay(GetWorld(), 2.f, info);
		DescriptionText = UKismetTextLibrary::Conv_StringToText("");
	}
	else {
		Player->Gold = Player->Gold - 5;
		RefreshGold(Player->Gold);
		Player->Armor = UKismetMathLibrary::Clamp(Player->Armor++, 0, Player->MaxArmor);
		RefreshArmor(Player->Armor);
	}
}

void UMerchant::OnClicked_Buy_Fire_potion_Button()
{
	if (Player->Potions.Num() < 2) {
		if (!Player->Potions.Contains(AFirePotion::StaticClass())) {
			if (Player->Gold < 5) {
				DescriptionText = DescriptionTexts[18];
				FLatentActionInfo info;
				info.Linkage = 0;
				info.CallbackTarget = this;
				UKismetSystemLibrary::Delay(GetWorld(), 2.f, info);
				DescriptionText = UKismetTextLibrary::Conv_StringToText("");
			}
			else {
				Player->Gold -= 5;
				RefreshGold(Player->Gold);
				Player->Potions.Add(AFirePotion::StaticClass());
				RefreshPotions();
			}
		}
		else {
			DescriptionText = DescriptionTexts[21];
		}
	}
	else {
		DescriptionText = DescriptionTexts[20];
	}
}

void UMerchant::OnClicked_Buy_Frost_potion_Button()
{
	if (Player->Potions.Num() < 2) {
		if (!Player->Potions.Contains(AFrostPotion::StaticClass())) {
			if (Player->Gold < 5) {
				DescriptionText = DescriptionTexts[18];
				FLatentActionInfo info;
				info.Linkage = 0;
				info.CallbackTarget = this;
				UKismetSystemLibrary::Delay(GetWorld(), 2.f, info);
				DescriptionText = UKismetTextLibrary::Conv_StringToText("");
			}
			else {
				Player->Gold -= 5;
				RefreshGold(Player->Gold);
				Player->Potions.Add(AFrostPotion::StaticClass());
				RefreshPotions();
			}
		}
		else {
			DescriptionText = DescriptionTexts[21];
		}
	}
	else {
		DescriptionText = DescriptionTexts[20];
	}
}

void UMerchant::OnClicked_Buy_Holy_potion_Button()
{
	if (Player->Potions.Num() < 2) {
		if (!Player->Potions.Contains(AHolyPotion::StaticClass())) {
			if (Player->Gold < 5) {
				DescriptionText = DescriptionTexts[18];
				FLatentActionInfo info;
				info.Linkage = 0;
				info.CallbackTarget = this;
				UKismetSystemLibrary::Delay(GetWorld(), 2.f, info);
				DescriptionText = UKismetTextLibrary::Conv_StringToText("");
			}
			else {
				Player->Gold -= 5;
				RefreshGold(Player->Gold);
				Player->Potions.Add(AHolyPotion::StaticClass());
				RefreshPotions();
			}
		}
		else {
			DescriptionText = DescriptionTexts[21];
		}
	}
	else {
		DescriptionText = DescriptionTexts[20];
	}
}

void UMerchant::OnClicked_Buy_Health_potion_Button()
{
	if (Player->Potions.Num() < 2) {
		if (!Player->Potions.Contains(AHealthPotion::StaticClass())) {
			if (Player->Gold < 5) {
				DescriptionText = DescriptionTexts[18];
				FLatentActionInfo info;
				info.Linkage = 0;
				info.CallbackTarget = this;
				UKismetSystemLibrary::Delay(GetWorld(), 2.f, info);
				DescriptionText = UKismetTextLibrary::Conv_StringToText("");
			}
			else {
				Player->Gold -= 5;
				RefreshGold(Player->Gold);
				Player->Potions.Add(AHealthPotion::StaticClass());
				RefreshPotions();
			}
		}
		else {
			DescriptionText = DescriptionTexts[21];
		}
	}
	else {
		DescriptionText = DescriptionTexts[20];
	}
}

void UMerchant::OnClicked_Buy_Perception_potion_Button()
{
	if (Player->Potions.Num() < 2) {
		if (!Player->Potions.Contains(APerceptionPotion::StaticClass())) {
			if (Player->Gold < 5) {
				DescriptionText = DescriptionTexts[18];
				FLatentActionInfo info;
				info.Linkage = 0;
				info.CallbackTarget = this;
				UKismetSystemLibrary::Delay(GetWorld(), 2.f, info);
				DescriptionText = UKismetTextLibrary::Conv_StringToText("");
			}
			else {
				Player->Gold -= 5;
				RefreshGold(Player->Gold);
				Player->Potions.Add(APerceptionPotion::StaticClass());
				RefreshPotions();
			}
		}
		else {
			DescriptionText = DescriptionTexts[21];
		}
	}
	else {
		DescriptionText = DescriptionTexts[20];
	}
}

void UMerchant::OnClicked_Buy_Poison_potion_Button()
{
	if (Player->Potions.Num() < 2) {
		if (!Player->Potions.Contains(APoisonPotion::StaticClass())) {
			if (Player->Gold < 5) {
				DescriptionText = DescriptionTexts[18];
				FLatentActionInfo info;
				info.Linkage = 0;
				info.CallbackTarget = this;
				UKismetSystemLibrary::Delay(GetWorld(), 2.f, info);
				DescriptionText = UKismetTextLibrary::Conv_StringToText("");
			}
			else {
				Player->Gold -= 5;
				RefreshGold(Player->Gold);
				Player->Potions.Add(APoisonPotion::StaticClass());
				RefreshPotions();
			}
		}
		else {
			DescriptionText = DescriptionTexts[21];
		}
	}
	else {
		DescriptionText = DescriptionTexts[20];
	}
}

void UMerchant::OnClicked_Sell_Fire_potion_Button()
{
	if (Player->Gold == Player->MaxGold) {
		DescriptionText = DescriptionTexts[23];
	}
	else {
		if (Player->Potions.Contains(AFirePotion::StaticClass())) {
			Player->Potions.Remove(AFirePotion::StaticClass());
			Player->Gold = UKismetMathLibrary::Clamp(Player->Gold + 3, 0, Player->MaxGold);
			RefreshGold(Player->Gold);
			RefreshPotions();
			Player->UpdateUserInterface();
		}
		else {
			DescriptionText = DescriptionTexts[22];
		}
	}
}

void UMerchant::OnClicked_Sell_Frost_potion_Button()
{
	if (Player->Gold == Player->MaxGold) {
		DescriptionText = DescriptionTexts[23];
	}
	else {
		if (Player->Potions.Contains(AFrostPotion::StaticClass())) {
			Player->Potions.Remove(AFrostPotion::StaticClass());
			Player->Gold = UKismetMathLibrary::Clamp(Player->Gold + 3, 0, Player->MaxGold);
			RefreshGold(Player->Gold);
			RefreshPotions();
			Player->UpdateUserInterface();
		}
		else {
			DescriptionText = DescriptionTexts[22];
		}
	}
}

void UMerchant::OnClicked_Sell_Holy_potion_Button()
{
	if (Player->Gold == Player->MaxGold) {
		DescriptionText = DescriptionTexts[23];
	}
	else {
		if (Player->Potions.Contains(AHolyPotion::StaticClass())) {
			Player->Potions.Remove(AHolyPotion::StaticClass());
			Player->Gold = UKismetMathLibrary::Clamp(Player->Gold + 3, 0, Player->MaxGold);
			RefreshGold(Player->Gold);
			RefreshPotions();
			Player->UpdateUserInterface();
		}
		else {
			DescriptionText = DescriptionTexts[22];
		}
	}
}

void UMerchant::OnClicked_Sell_Health_potion_Button()
{
	if (Player->Gold == Player->MaxGold) {
		DescriptionText = DescriptionTexts[23];
	}
	else {
		if (Player->Potions.Contains(AHealthPotion::StaticClass())) {
			Player->Potions.Remove(AHealthPotion::StaticClass());
			Player->Gold = UKismetMathLibrary::Clamp(Player->Gold + 3, 0, Player->MaxGold);
			RefreshGold(Player->Gold);
			RefreshPotions();
			Player->UpdateUserInterface();
		}
		else {
			DescriptionText = DescriptionTexts[22];
		}
	}
}

void UMerchant::OnClicked_Sell_Perception_potion_Button()
{
	if (Player->Gold == Player->MaxGold) {
		DescriptionText = DescriptionTexts[23];
	}
	else {
		if (Player->Potions.Contains(APerceptionPotion::StaticClass())) {
			Player->Potions.Remove(APerceptionPotion::StaticClass());
			Player->Gold = UKismetMathLibrary::Clamp(Player->Gold + 3, 0, Player->MaxGold);
			RefreshGold(Player->Gold);
			RefreshPotions();
			Player->UpdateUserInterface();
		}
		else {
			DescriptionText = DescriptionTexts[22];
		}
	}
}

void UMerchant::OnClicked_Sell_Poison_potion_Button()
{
	if (Player->Gold == Player->MaxGold) {
		DescriptionText = DescriptionTexts[23];
	}
	else {
		if (Player->Potions.Contains(APoisonPotion::StaticClass())) {
			Player->Potions.Remove(APoisonPotion::StaticClass());
			Player->Gold = UKismetMathLibrary::Clamp(Player->Gold + 3, 0, Player->MaxGold);
			RefreshGold(Player->Gold);
			RefreshPotions();
			Player->UpdateUserInterface();
		}
		else {
			DescriptionText = DescriptionTexts[22];
		}
	}
}

void UMerchant::OnHovered_Option1()
{
	DescriptionText = DescriptionTexts[0];
}

void UMerchant::OnUnhovered_Option1()
{
	DescriptionText = UKismetTextLibrary::Conv_StringToText("");
}

void UMerchant::OnHovered_Option2()
{
	DescriptionText = DescriptionTexts[1];
}

void UMerchant::OnUnhovered_Option2()
{
	DescriptionText = UKismetTextLibrary::Conv_StringToText("");
}

void UMerchant::OnHovered_Option3()
{
	DescriptionText = DescriptionTexts[2];
}

void UMerchant::OnUnhovered_Option3()
{
	DescriptionText = UKismetTextLibrary::Conv_StringToText("");
}

void UMerchant::OnHovered_Option4()
{
	DescriptionText = DescriptionTexts[3];
}

void UMerchant::OnUnhovered_Option4()
{
	DescriptionText = UKismetTextLibrary::Conv_StringToText("");
}

void UMerchant::OnHovered_Option5()
{
	DescriptionText = DescriptionTexts[4];
}

void UMerchant::OnUnhovered_Option5()
{
	DescriptionText = UKismetTextLibrary::Conv_StringToText("");
}

void UMerchant::OnHovered_Sell_Option1()
{
	DescriptionText = DescriptionTexts[5];
}

void UMerchant::OnUnhovered_Sell_Option1()
{
	DescriptionText = UKismetTextLibrary::Conv_StringToText("");
}

void UMerchant::OnHovered_Buy_Fire_potion_Button()
{
	DescriptionText = DescriptionTexts[6];
}

void UMerchant::OnUnhovered_Buy_Fire_potion_Button()
{
	DescriptionText = UKismetTextLibrary::Conv_StringToText("");
}

void UMerchant::OnHovered_Buy_Frost_potion_Button()
{
	DescriptionText = DescriptionTexts[7];
}

void UMerchant::OnUnhovered_Buy_Frost_potion_Button()
{
	DescriptionText = UKismetTextLibrary::Conv_StringToText("");
}

void UMerchant::OnHovered_Buy_Health_potion_Button()
{
	DescriptionText = DescriptionTexts[8];
}

void UMerchant::OnUnhovered_Buy_Health_potion_Button()
{
	DescriptionText = UKismetTextLibrary::Conv_StringToText("");
}

void UMerchant::OnHovered_Buy_Holy_potion_Button()
{
	DescriptionText = DescriptionTexts[9];
}

void UMerchant::OnUnhovered_Buy_Holy_potion_Button()
{
	DescriptionText = UKismetTextLibrary::Conv_StringToText("");
}

void UMerchant::OnHovered_Buy_Perception_potion_Button()
{
	DescriptionText = DescriptionTexts[10];
}

void UMerchant::OnUnhovered_Buy_Perception_potion_Button()
{
	DescriptionText = UKismetTextLibrary::Conv_StringToText("");
}

void UMerchant::OnHovered_Buy_Poison_potion_Button()
{
	DescriptionText = DescriptionTexts[11];
}

void UMerchant::OnUnhovered_Buy_Poison_potion_Button()
{
	DescriptionText = UKismetTextLibrary::Conv_StringToText("");
}

void UMerchant::OnHovered_Sell_Fire_potion_Button()
{
	DescriptionText = DescriptionTexts[12];
}

void UMerchant::OnUnhovered_Sell_Fire_potion_Button()
{
	DescriptionText = UKismetTextLibrary::Conv_StringToText("");
}

void UMerchant::OnHovered_Sell_Frost_potion_Button()
{
	DescriptionText = DescriptionTexts[13];
}

void UMerchant::OnUnhovered_Sell_Frost_potion_Button()
{
	DescriptionText = UKismetTextLibrary::Conv_StringToText("");
}

void UMerchant::OnHovered_Sell_Health_potion_Button()
{
	DescriptionText = DescriptionTexts[14];
}

void UMerchant::OnUnhovered_Sell_Health_potion_Button()
{
	DescriptionText = UKismetTextLibrary::Conv_StringToText("");
}

void UMerchant::OnHovered_Sell_Holy_potion_Button()
{
	DescriptionText = DescriptionTexts[15];
}

void UMerchant::OnUnhovered_Sell_Holy_potion_Button()
{
	DescriptionText = UKismetTextLibrary::Conv_StringToText("");
}

void UMerchant::OnHovered_Sell_Perception_potion_Button()
{
	DescriptionText = DescriptionTexts[16];
}

void UMerchant::OnUnhovered_Sell_Perception_potion_Button()
{
	DescriptionText = UKismetTextLibrary::Conv_StringToText("");
}

void UMerchant::OnHovered_Sell_Poison_potion_Button()
{
	DescriptionText = DescriptionTexts[17];
}

void UMerchant::OnUnhovered_Sell_Poison_potion_Button()
{
	DescriptionText = UKismetTextLibrary::Conv_StringToText("");
}
