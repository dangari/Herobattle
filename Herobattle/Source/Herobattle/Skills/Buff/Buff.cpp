#include "Herobattle.h"
#include "Buff.h"
#include "../Components/BaseSkillComponent.h"
#include "Base/BaseCharacter.h"
#include "../XMLSkillReader.h"
#include "AI/AISimCharacter.h"
#include "BcHeal.h"
#include "BcWhenCondition.h"
#include "BcForEach.h"
#include "BcBlock.h"
#include "BcGiveMana.h"
#include "BcReduceMana.h"
#include "BcRegenaration.h"
#include "BcDamageReduction.h"
#include "BcAttackSpeed.h"
#include "BcMovementSpeed.h"
#include "BcAdrenaline.h"


TMap<FString, bCclassFuncPtr>  UBuff::bcObjectNameList;

UBuff::UBuff()
{

	bcObjectNameList.Add(TEXT("heal"), &createBcInstance<UBcHeal>);
	bcObjectNameList.Add(TEXT("when"), &createBcInstance<UBcWhenCondition>);
	bcObjectNameList.Add(TEXT("foreach"), &createBcInstance<UBcForEach>);
	bcObjectNameList.Add(TEXT("block"), &createBcInstance<UBcBlock>);
	bcObjectNameList.Add(TEXT("givemana"), &createBcInstance<UBcGiveMana>);
	bcObjectNameList.Add(TEXT("reducemanacost"), &createBcInstance<UBcReduceMana>);
	bcObjectNameList.Add(TEXT("regeneration"), &createBcInstance<UBcRegenaration>);
	bcObjectNameList.Add(TEXT("damagereduction"), &createBcInstance<UBcDamageReduction>);
	bcObjectNameList.Add(TEXT("attackspeed"), &createBcInstance<UBcAttackSpeed>);
	bcObjectNameList.Add(TEXT("movementspeed"), &createBcInstance<UBcMovementSpeed>);
	bcObjectNameList.Add(TEXT("giveadrenaline"), &createBcInstance<UBcAdrenaline>);
}


UBuff::~UBuff()
{
}

void UBuff::init(ABaseCharacter* owner, TArray<FBuffContainer> bCBuffList, float duration, FString name, FString usage, FSkillProperties properties, UBuff* ownerBuff)
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

		bCclassFuncPtr createFunc = *(bcObjectNameList.Find(buff.buffName));
		UBaseBuffCompenent* bC = createFunc(ownerBuff);
		bC->init(buff, owner, properties, ownerBuff);
		m_BcList.Add(bC);

	}
}


void UBuff::initSim(UAISimCharacter* owner, TArray<FBuffContainer> bCBuffList, float duration, FString name, FString usage, FSkillProperties properties, UBuff* ownerBuff)
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

		bCclassFuncPtr createFunc = *(bcObjectNameList.Find(buff.buffName));
		UBaseBuffCompenent* bC = createFunc(ownerBuff);
		bC->initSim(buff, owner, properties, ownerBuff);
		m_BcList.Add(bC);

	}
}

void UBuff::initDummyBuff()
{
	m_Duration = 10.f;
	m_Name = TEXT("Dummy Buff");
	m_IsInfinityUsage = true;
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

bool UBuff::runSim(UAISimCharacter* target, UAISimCharacter* self, int value /*= 0*/)
{

	bool b = true;
	for (auto& sc : m_BcList)
	{
		b = sc->runSim(target, self, value);
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

float UBuff::getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	
	for (auto& bC : m_BcList)
	{
		bC->getScoreSim(caster, characterState, skillScore, m_Duration);
	}
	return 1.f;
}

FString UBuff::getName()
{
	return m_Name;
}

UBuff* UBuff::copy()
{
	UBuff* buff = NewObject<UBuff>();
	buff->m_Duration = m_Duration; 
	buff->m_Name = m_Name;
	buff->m_IsInfinityUsage = m_IsInfinityUsage;
	buff->m_Usage = m_Usage;
	
	for (auto& bC : m_BcList)
	{
		buff->m_BcList.Add(bC);
	}
	
	return buff;
}
