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
	bool b = true;

	for (auto& sc : sCBuffList)
	{
		b = sc->run(target, self);
	}
	return b;
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
		tagName = buffs->GetTag();
		if (XMLSkillReader::scObjectNameList.Contains(tagName))
		{
			classFuncPtr createFunc = *(XMLSkillReader::scObjectNameList.Find(tagName));
			UBaseSkillComponent* sc = createFunc();
			sc->init(buffs);
			sCBuffList.Add(sc);
		}
	}
}

FString UScBuff::ToString()
{
	//FString sCText = Super::ToString();
	//sCText.Append(TEXT(" \n ");
	return TEXT("");
}