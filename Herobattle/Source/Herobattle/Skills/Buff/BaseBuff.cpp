#include "Herobattle.h"
#include "BaseBuff.h"
#include "../Components/BaseSkillComponent.h"
#include "Base/BaseCharacter.h"


UBaseBuff::UBaseBuff()
{
}


UBaseBuff::~UBaseBuff()
{
}

void UBaseBuff::init(TArray<UBaseSkillComponent*> scList, float duration, FString name, FString usage)
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


bool UBaseBuff::run(ABaseCharacter* target, ABaseCharacter* self)
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

void UBaseBuff::updateDuration(float deltaTime)
{
	m_Duration -= deltaTime;
}

bool UBaseBuff::isExpired()
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

FString UBaseBuff::getName()
{
	return m_Name;
}
