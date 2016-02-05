// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "Logging.h"
#include "HeroBattleHero.h"




void ULogging::addHealth(float value, float timeStamp, FString name)
{
	if (health.Contains(name))
	{
		health.Find(name)->timeStamps.Add(timeStamp);
		health.Find(name)->valueArray.Add(value);
	}
	else
	{
		FSimpleArray simpleArray;
		simpleArray.timeStamps.Add(timeStamp);
		simpleArray.valueArray.Add(timeStamp);
		health.Add(name, simpleArray);
	}
}

void ULogging::addMana(float value, float timeStamp, FString name)
{
	if (mana.Contains(name))
	{
		mana.Find(name)->timeStamps.Add(timeStamp);
		mana.Find(name)->valueArray.Add(value);
	}
	else
	{
		FSimpleArray simpleArray;
		simpleArray.timeStamps.Add(timeStamp);
		simpleArray.valueArray.Add(timeStamp);
		mana.Add(name, simpleArray);
	}
}

void ULogging::addSkill(int slot, FString name)
{
	if (skill.Contains(name))
	{
		skill.Find(name)->timeStamps.Add(m_completeTime);
		skill.Find(name)->slotArray.Add(slot);
	}
	else
	{
		FSimpleArray simpleArray;
		simpleArray.timeStamps.Add(m_completeTime);
		simpleArray.slotArray.Add(slot);
		skill.Add(name, simpleArray);
	}
}

void ULogging::update(float DeltaTime)
{
	m_timeStamp += DeltaTime;
	m_completeTime += DeltaTime;
	if (m_timeStamp > 1)
	{
		m_timeStamp = 0;
		for (auto& hero : heroes)
		{
			addHealth(hero->m_Health, m_completeTime, hero->m_Name);
			addMana(hero->m_Mana, m_completeTime, hero->m_Name);
		}
	}
	if (m_completeTime > 180)
	{
		//do something
	}
}
