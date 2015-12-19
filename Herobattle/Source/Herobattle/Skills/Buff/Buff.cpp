#include "Herobattle.h"
#include "Buff.h"
#include "../Components/BaseSkillComponent.h"
#include "Base/BaseCharacter.h"
#include "../XMLSkillReader.h"


UBuff::UBuff()
{
}


UBuff::~UBuff()
{
}

void UBuff::init(ABaseCharacter* owner, TArray<FBuffContainer> bCBuffList, float duration, FString name, FString usage, FSkillProperties properties)
{
	
	m_Duration = duration;
	m_Name = name;

	//set Usage if not infinte
	if (usage.Equals(TEXT("INF")))
	{
		m_IsInfinityUsage = true;
	}
	else
	{
		m_IsInfinityUsage = false;
		m_Usage = FCString::Atoi(*usage);
	}

	for (auto& buff : bCBuffList)
	{

		bCclassFuncPtr createFunc = *(XMLSkillReader::bcObjectNameList.Find(buff.buffName));
		UBaseBuffCompenent* bC = createFunc();
		bC->init(buff, owner, properties);
		m_BcList.Add(bC);

	}
}


bool UBuff::run(ABaseCharacter* target, ABaseCharacter* self, int value)
{
	bool b = true;
	for (auto& sc : m_BcList)
	{
		b = sc->run(target, self,value);
	}
	if (b && !m_IsInfinityUsage)
		m_Usage--;
	return b;
}

void UBuff::updateBuff(float deltaTime)
{
	m_Duration -= deltaTime;
	for (auto& bC : m_BcList)
	{
		bC->update(deltaTime);
	}
}

bool UBuff::isExpired()
{
	if (m_Duration <= 0 || (m_Usage <= 0 && !m_IsInfinityUsage))
		return true;
	bool b = false;
	for (auto& sc : m_BcList)
	{
		b = sc->isExpired();
	}
	return b;
}

float UBuff::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	for (auto& bC : m_BcList)
	{
		bC->getScore(caster, characterState, skillScore, m_Duration);
	}
	return 1.f;
}

FString UBuff::getName()
{
	return m_Name;
}
