// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "Engine.h"
#include "Skill.h"
#include "Components/BaseSkillComponent.h"
#include "Base/BaseCharacter.h"
#include "UnrealNetwork.h"
#include "SkillMessages.h"
#include "AI/AIGameState.h"



USkill::USkill()
{
	name = TEXT("default");
}

USkill::~USkill()
{
}

bool USkill::run(ABaseCharacter* target, ABaseCharacter* self)
{
	bool b = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, name);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(manaCost));
	for (auto& sc : componentList)
	{
		b = sc->run(target, self);
	}

	return b;
}

bool USkill::isValidTarget(ABaseCharacter* target, ABaseCharacter* self)
{
	if (target->isEnemy(self->ETeam) && targetType == TargetType::ENEMY)
	{
		return true;
	}
	else if (!(target->isEnemy(self->ETeam)) && targetType == TargetType::SELFFREND)
	{
		return true;
	}
	else if (!(target->isEnemy(self->ETeam)) && targetType == TargetType::FRIEND && target != self)
	{
		return true;
	}
	else if (target == self && targetType == TargetType::SELF)
	{
		return true;
	}
	else
	{
		self->messages->registerMessage(TEXT("Invalide Target"), MessageType::SKILLERROR);
		return false;
	}
}

float USkill::getScore(UAIGameState* aiGameState)
{
	return 1.0f;
}

void USkill::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(USkill, componentList);
}
