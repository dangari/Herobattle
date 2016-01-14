// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "ScBuff.h"
#include "../../Base/BaseCharacter.h"
#include "../XMLSkillReader.h"
#include "../Buff/Buff.h"
#include "../Buff/BuffContainer.h"
#include "AI/SkillScore.h"
#include "AI/CharacterState.h"

UScBuff::UScBuff()
{
	componentName = TEXT("Buff");
}


UScBuff::~UScBuff()
{
}


bool UScBuff::run(ABaseCharacter* target, ABaseCharacter* self, FString SkillName /*= TEXT("Name")*/)
{
	bool b = true;

	UBuff* buff = NewObject<UBuff>(target);
	float duration = scaleTable[self->getAttributeValue(scaleAttribute)];
	buff->init(self, bCBuffList, duration, SkillName, m_Usage, m_properties, buff);
	target->applyBuff(buff, m_Trigger);
	return b;
}

bool UScBuff::runSim(UAISimCharacter* target, UAISimCharacter* self, FString SkillName /*= TEXT("Name")*/)
{
	bool b = true;

	UBuff* buff = NewObject<UBuff>(target);
	float duration = scaleTable[self->getAttributeValue(scaleAttribute)];
	buff->initSim(self, bCBuffList, duration, SkillName, m_Usage, m_properties, buff);
	target->applyBuff(buff, m_Trigger);
	return b;
}

float UScBuff::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	UBuff* buff = NewObject<UBuff>(this);
	float duration = scaleTable[caster->getAttributeValue(scaleAttribute)];
	buff->init(caster, bCBuffList, duration, SkillName, m_Usage, m_properties, buff);
	buff->getScore(caster, characterState, skillScore);
	DestroyObject(buff);
	return 1.f;
}

float UScBuff::getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	UBuff* buff = NewObject<UBuff>(this);
	float duration = scaleTable[caster->getAttributeValue(scaleAttribute)];
	buff->initSim(caster, bCBuffList, duration, SkillName, m_Usage, m_properties, buff);
	buff->getScoreSim(caster, characterState, skillScore);
	DestroyObject(buff);
	return 1.f;
}

void UScBuff::init(FXmlNode* node, FSkillProperties properties)
{
	Super::init(node, properties);
	// the skill type of the buff like stance, enchantment ...
	FString cType = node->GetAttribute(TEXT("type"));
	this->skillType = SkillEnums::stringToSkillType(cType);

	// reads the usage of the buff
	m_Usage = node->GetAttribute((TEXT("usage")));
	m_Trigger = SkillEnums::stringToTrigger(node->GetAttribute(TEXT("trigger")));
	FString tagName = node->GetTag();
	if (tagName.Equals(TEXT("buff")))
	{
		fillScaleTable(node);

		TArray<FXmlNode*> buffList = node->GetChildrenNodes();
		for (auto& buffs : buffList)
		{
			tagName = buffs->GetTag();
			if (UBuff::bcObjectNameList.Contains(tagName))
			{
				FBuffContainer buff;
				buff.buffName = tagName;
				buff.targetType = SkillEnums::stringToTargetType(buffs->GetAttribute(TEXT("target")));
				buff.node = buffs;
				buff.fillScaleTable(buffs);
				bCBuffList.Add(buff);
			}
		}
	}
}

FString UScBuff::ToString()
{
	FString sCText = componentName;
	sCText.Append(TEXT(" \n "));
	sCText.Append(Super::ToString());
	sCText.Append(TEXT(" \n"));
	for (auto& bC : bCBuffList)
	{
		sCText.Append(TEXT("\t)"));
		sCText.Append(bC.ToString());
	}
	return sCText;
}

UBuff* UScBuff::createBuff(float duration)
{
	/*TArray<UBaseSkillComponent*> scList;
	for (auto& createFunc : sCBuffList)
	{
	UBaseSkillComponent* sc = createFunc();
	scList.Add(sc);
	}

	UBuff* buff = NewObject<UBuff>();
	buff->init(scList, duration, SkillName, m_Usage);
	return buff;*/
	return nullptr;
}
