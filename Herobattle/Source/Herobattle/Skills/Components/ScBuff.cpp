// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "ScBuff.h"
#include "../../Base/BaseCharacter.h"
#include "../XMLSkillReader.h"
UScBuff::UScBuff()
{
	//damageType = HBDamageType::FIRE;
}


UScBuff::~UScBuff()
{
}


bool UScBuff::run(ABaseCharacter* target, ABaseCharacter* self)
{
	Super::run(target, self);
	float damage = scaleTable[self->getAttributeValue(scaleAttribute)];
	//target->damage(damage, damageType);
	return true;
}

float UScBuff::getScore()
{
	return 1.f;
}

void UScBuff::init(FXmlNode* node)
{
	FString cType = node->GetAttribute(TEXT("type"));
	this->skillType = SkillEnums::stringToSkillType(cType);
	FString tagName = node->GetTag();
	if (tagName.Equals(TEXT("buff")))
	{
		fillScaleTable(node);
	}
	TArray<FXmlNode*> buffList = node->GetChildrenNodes();
	for (auto& buffs : buffList)
	{
		if (XMLSkillReader::scObjectNameList.Contains(tagName))
		{
			classFuncPtr createFunc = *(XMLSkillReader::scObjectNameList.Find(tagName));
			UBaseSkillComponent* sc = createFunc();
			sc->init(buffs);
			sCBuffList.Add(sc);
		}
	}
}

