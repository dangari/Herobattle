// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "AISimCharacter.h"
#include "Skills/Condition/BaseCondition.h"
#include "Skills/Buff/Buff.h"




void AAISimCharacter::init(FCharacterState state)
{
	ETeam = state.ETeam;
	weapon = state.weapon;
	m_location = state.location;
	m_MaxHealth = state.self->m_MaxHealth;
	m_Health = state.self->m_Health;
	m_State = state.state;

	m_isCasting = state.isCasting;
	m_isAutoAttacking = state.isAutoAttacking;
	m_isBuffed = state.isBuffed;
	m_isHexed = state.isHexed;

	m_hasStance = state.hasStance;

	applyCondition(state.conditions);

	if (m_isBuffed)
	{
		applyDummyBuff();
	}
	
}



void AAISimCharacter::init(ABaseCharacter* character)
{
	/*for (auto& bC : character->m_BuffList)
	{

	}*/
}

void AAISimCharacter::applyCondition(TArray<Condition> conditions)
{
	for (auto& condi : conditions)
	{
		UBaseCondition* simCondi = NewObject<UBaseCondition>();
		simCondi->init(condi, 10);
		ABaseCharacter::applyCondition(simCondi);
	}
}

void AAISimCharacter::applyDummyBuff()
{
	UBuff* dummyBuff = NewObject<UBuff>();
	dummyBuff->initDummyBuff();
	applyBuff(dummyBuff, Trigger::NONE);
}
