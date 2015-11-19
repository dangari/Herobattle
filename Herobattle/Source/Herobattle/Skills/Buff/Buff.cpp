#include "Herobattle.h"
#include "Buff.h"
#include "../Components/BaseSkillComponent.h"
#include "Base/BaseCharacter.h"


UBuff::UBuff()
{
}


UBuff::~UBuff()
{
}

void UBuff::init(TArray<UBaseSkillComponent*> scList, float duration, FString name, FString usage)
{
	m_ScList = scList;
	m_Duration = duration;
	m_Name = name;
	if (usage.Equals(TEXT("INF")))
	{
		m_IsInfinityUsage = true;
	}
	else
	{
		m_IsInfinityUsage = false;
		m_Usage = FCString::Atoi(*usage);
	}
}


bool UBuff::run(ABaseCharacter* target, ABaseCharacter* self)
{
	bool b = true;
	for (auto& sc : m_ScList)
	{
		b = sc->run(target, self);
	}
	if (b && !m_IsInfinityUsage)
		m_Usage--;
	return b;
}

void UBuff::updateDuration(float deltaTime)
{
	m_Duration -= deltaTime;
}

bool UBuff::isExpired()
{
	if (m_Duration <= 0 || m_Usage <= 0)
		return true;
	bool b = false;
	for (auto& sc : m_ScList)
	{
		b = sc->isExpired();
	}
	return b;
}

FString UBuff::getName()
{
	return m_Name;
}
