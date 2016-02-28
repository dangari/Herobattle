// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "ScForEach.h"
#include "XmlParser.h"
#include "../XMLSkillReader.h"
#include "Base/BaseCharacter.h"
#include "AI/AISimCharacter.h"
#include "AI/SkillScore.h"


UScForEach::UScForEach()
{
	componentName = TEXT("ForEach");
}

UScForEach::~UScForEach()
{

}

bool UScForEach::run(ABaseCharacter* target, ABaseCharacter* self, FString SkillName /*= TEXT("Name")*/)
{
	bool b = true;
	uint8 count = 0;
	if (skillType.Equals(TEXT("CONDITION")))
	{
		count = target->getCondtionCount();
	}
	if (count > 0){
		for (int i = 1; i <= count; i++)
		{
			for (auto& scObj : scList)
			{
				b= scObj->run(target, self);
			}
		}
	}
	return b;
}

bool UScForEach::runSim(UAISimCharacter* target, UAISimCharacter* self, FString SkillName /*= TEXT("Name")*/)
{
	bool b = true;
	uint8 count = 0;
	if (skillType.Equals(TEXT("CONDITION")))
	{
		count = target->getCondtionCount();
	}
	if (count > 0){
		for (int i = 1; i <= count; i++)
		{
			for (auto& scObj : scList)
			{
				b = scObj->runSim(target, self);
			}
		}
	}
	return b;
}

void UScForEach::init(FXmlNode* node, FSkillProperties properties)
{
	Super::init(node, properties);
	skillType = node->GetAttribute(TEXT("type"));
	TArray<FXmlNode*> childNodes = node->GetChildrenNodes();
	for (auto& scObj : childNodes)
	{
		FString tagName = scObj->GetTag();
		if (XMLSkillReader::scObjectNameList.Contains(tagName))
		{
			classFuncPtr createFunc = *(XMLSkillReader::scObjectNameList.Find(tagName));
			UBaseSkillComponent* sc = createFunc(this);
			sc->init(scObj, properties);
			scList.Add(sc);
		}
	}
}

float UScForEach::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	uint8 count = 0;
	if (skillType.Equals(TEXT("CONDITION")))
	{
		count = characterState.conditions.Num();
	}
	if (count > 0){
		for (int i = 1; i <= count; i++)
		{
			for (auto& scObj : scList)
			{
				scObj->getScore(caster, characterState, skillScore);
			}
		}
	}
	else
	{
		skillScore->addScore(0.f, componentName);
	}
	return 0.f;
}

float UScForEach::getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	uint8 count = 0;
	if (skillType.Equals(TEXT("CONDITION")))
	{
		count = characterState.conditions.Num();
	}
	if (count > 0){
		for (int i = 1; i <= count; i++)
		{
			for (auto& scObj : scList)
			{
				scObj->getScoreSim(caster, characterState, skillScore);
			}
		}
	}
	else
	{
		skillScore->addScore(0.f, componentName);
	}
	return 0.f;
}
