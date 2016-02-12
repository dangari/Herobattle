// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "Logging.h"
#include "HeroBattleHero.h"




ULogging::ULogging()
{
	loggingOn = false;
}

ULogging::~ULogging()
{

}

void ULogging::addHealth(float value, float timeStamp, FString name)
{
	if (loggingOn)
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
}

void ULogging::addMana(float value, float timeStamp, FString name)
{
	if (loggingOn)
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
}

void ULogging::addSkill(int slot, FString name)
{
	if (loggingOn)
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
}

void ULogging::update(float DeltaTime)
{
	if (loggingOn)
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
		if (m_completeTime > 120 && !isPrinted)
		{
			printToLog();
			isPrinted = true;
		}
	}
}

void ULogging::printToLog()
{
	FString values = TEXT("");
	FString timeStamps = TEXT("");
	//skill log
	for (auto& element : skill)
	{
		FSimpleArray valueArray = element.Value;
		values = values.Append(element.Key).Append(TEXT("|")).Append(valueArray.slotsToString());
		timeStamps = timeStamps.Append(*element.Key).Append(TEXT("|")).Append(valueArray.timeStampsToString());
		UE_LOG(SkillLog, Log, TEXT("%s"), *values);
		UE_LOG(SkillLog, Log, TEXT("%s"), *timeStamps);
		values = TEXT("");
		timeStamps = TEXT("");
	}
	//health log
	for (auto& element : health)
	{
		FSimpleArray valueArray = element.Value;
		values = values.Append(element.Key).Append(TEXT("|")).Append(valueArray.valueToString());
		timeStamps = timeStamps.Append(*element.Key).Append(TEXT("|")).Append(valueArray.timeStampsToString());
		UE_LOG(HealthLog, Log, TEXT("%s"), *values);
		UE_LOG(HealthLog, Log, TEXT("%s"), *timeStamps);
		values = TEXT("");
		timeStamps = TEXT("");
	}
	//mana log
	for (auto& element : mana)
	{
		FSimpleArray valueArray = element.Value;
		values = values.Append(element.Key).Append(TEXT("|")).Append(valueArray.valueToString());
		timeStamps = timeStamps.Append(*element.Key).Append(TEXT("|")).Append(valueArray.timeStampsToString());
		UE_LOG(ManaLog, Log, TEXT("%s"), *values);
		UE_LOG(ManaLog, Log, TEXT("%s"), *timeStamps);
		values = TEXT("");
		timeStamps = TEXT("");
	}


}

FString FSimpleArray::valueToString()
{
	return arrayToString(valueArray, TEXT("values"));
}

FString FSimpleArray::timeStampsToString()
{
	return arrayToString(timeStamps, TEXT("timeStamps"));
}

FString FSimpleArray::slotsToString()
{
	FString s = TEXT(" ");
	s = s.Append("slot").Append(TEXT("|"));
	for (auto& element : slotArray)
	{
		int32 value = element;
		s.AppendInt(value);
		s.Append(TEXT("|"));
	}

	return s;
}

FString FSimpleArray::arrayToString(TArray<float> array, FString name)
{
	FString s = TEXT(" ");
	s = s.Append(name).Append(TEXT("|"));
	for (auto& element : array)
	{
		FString value = FString::SanitizeFloat(element);
		s = s.Append(value).Append(TEXT("|"));
	}

	return s;
}
