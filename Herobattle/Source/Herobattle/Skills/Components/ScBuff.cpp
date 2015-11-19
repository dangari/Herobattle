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

	//UBuff* buff = createBuff(self->getAttributeValue(scaleAttribute));
	//target->applyBuff(buff);
	return b;
}

float UScBuff::getScore()
{
	return 1.f;
}

void UScBuff::init(FXmlNode* node)
{
	FString cType = node->GetAttribute(TEXT("type"));
	m_Usage = node->GetAttribute((TEXT("usage")));
	this->skillType = SkillEnums::stringToSkillType(cType);
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
