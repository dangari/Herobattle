// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "ScBuff.h"
#include "../../Base/BaseCharacter.h"
#include "../XMLSkillReader.h"
#include "../Buff/BaseBuff.h"
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

	UBaseBuff* buff = createBuff(self->getAttributeValue(scaleAttribute));
	target->applyBuff(buff);
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
	}
	TArray<FXmlNode*> buffList = node->GetChildrenNodes();
	for (auto& buffs : buffList)
	{
		tagName = buffs->GetTag();
		if (XMLSkillReader::scObjectNameList.Contains(tagName))
		{
			classFuncPtr createFunc = *(XMLSkillReader::scObjectNameList.Find(tagName));
			sCBuffList.Add(createFunc);
		}
	}
}

FString UScBuff::ToString()
{
	//FString sCText = Super::ToString();
	//sCText.Append(TEXT(" \n ");
	return TEXT("");
}

UBaseBuff* UScBuff::createBuff(float duration)
{
	TArray<UBaseSkillComponent*> scList;
	for (auto& createFunc : sCBuffList)
	{
		UBaseSkillComponent* sc = createFunc();
		scList.Add(sc);
	}

	UBaseBuff* buff = NewObject<UBaseBuff>();
	buff->init(scList, duration, SkillName, m_Usage);
	return buff;
}
