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



void AAISimCharacter::init(FCharacterProperties properties)
{
	m_MaxHealth = properties.m_MaxHealth;
	m_Health = properties.m_Health;
	m_MaxMana = properties.m_MaxMana;
	m_Mana = properties.m_Mana;
	m_ManaRegeneration = properties.m_ManaRegeneration;
	ETeam = properties.ETeam;
	proffession = properties.proffession;
	m_BuffList = properties.m_BuffList;
	attrList = properties.attrList;
	weapon = properties.weapon;
	m_State = properties.m_State;
	m_ManaReduction = properties.m_ManaReduction;
	m_DamageReduction = properties.m_DamageReduction;
	m_HealthBuffRegneration = properties.m_HealthBuffRegneration;
	m_ManaBuffRegneration = properties.m_ManaBuffRegneration;


	for (auto& elem : properties.m_CompleteBuffList)
	{
		FBuffList buffList = elem.Value;
		FBuffList newBuffList;
		Trigger trigger = elem.Key;
		for (auto& item : buffList.m_BuffList)
		{
			UBuff* buff = item.Value;
			UBuff* newBuff = buff->copy();
			newBuffList.m_BuffList.Add(newBuff->m_Name, newBuff);
		}
		m_CompleteBuffList.Add(trigger, newBuffList);

	}

	for (int i = 0; i < 8; i++)
	{
		skillList[i] = properties.skillList[i];
		skillcooldowns[i] = properties.skillcooldowns[i];
		m_AdrenalineList[i] = properties.m_AdrenalineList[i];
	}


	for (auto& elem : properties.m_condtionList)
	{
		UBaseCondition* condi = elem.Value;
		UBaseCondition* condition = UBaseCondition::MAKE(condi->condition, condi->currentDuration);
		ABaseCharacter::applyCondition(condi);
	}
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
