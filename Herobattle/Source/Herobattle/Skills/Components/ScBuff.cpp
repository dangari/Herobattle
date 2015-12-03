// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "ScBuff.h"
#include "../../Base/BaseCharacter.h"
#include "../XMLSkillReader.h"
#include "../Buff/Buff.h"
#include "../Buff/BuffContainer.h"
UScBuff::UScBuff()
{
	//damageType = HBDamageType::FIRE;
}


UScBuff::~UScBuff()
{
}


bool UScBuff::run(ABaseCharacter* target, ABaseCharacter* self)
{
	bool b = true;

	UBuff* buff = NewObject<UBuff>();
	float duration = scaleTable[self->getAttributeValue(scaleAttribute)];
	buff->init(self, bCBuffList, duration, TEXT("name"), m_Usage);
	target->applyBuff(buff);
	return b;
}

float UScBuff::getScore(FCharacterState characterState)
{
	return 1.f;
}

void UScBuff::init(FXmlNode* node)
{
	// the skill type of the buff like stance, enchantment ...
	FString cType = node->GetAttribute(TEXT("type"));
	this->skillType = SkillEnums::stringToSkillType(cType);

	// reads the usage of the buff
	m_Usage = node->GetAttribute((TEXT("usage")));
	
	FString tagName = node->GetTag();
	if (tagName.Equals(TEXT("buff")))
	{
		fillScaleTable(node);

		TArray<FXmlNode*> buffList = node->GetChildrenNodes();
		for (auto& buffs : buffList)
		{
			tagName = buffs->GetTag();
			if (XMLSkillReader::bcObjectNameList.Contains(tagName))
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
	//FString sCText = Super::ToString();
	//sCText.Append(TEXT(" \n ");
	return TEXT("");
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
