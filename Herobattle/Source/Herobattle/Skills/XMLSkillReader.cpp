// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "XMLSkillReader.h"
#include "XmlParser.h"
#include "Engine.h"
#include "Skill.h"

//Skill Components
#include "Components/BaseSkillComponent.h"
#include "Components/ScHeal.h"
#include "Components/ScDamage.h"
#include "Components/ScCondition.h"
#include "Components/ScWhenCondition.h"
#include "Components/ScBuff.h"
#include "Components/ScForEach.h"

//Buff Components
#include "Buff/BaseBuffCompenent.h"
#include "Buff/BcHeal.h"
#include "Buff/BcWhenCondition.h"
#include "Buff/BcForEach.h"



TMap<FString, classFuncPtr> XMLSkillReader::scObjectNameList;
TMap<FString, bCclassFuncPtr> XMLSkillReader::bcObjectNameList;


XMLSkillReader::XMLSkillReader()
{

	//Fill scObjectNameList
	scObjectNameList.Add(TEXT("damage"), &createScInstance<UScDamage>);
	scObjectNameList.Add(TEXT("heal"), &createScInstance<UScHeal>);
	scObjectNameList.Add(TEXT("condition"), &createScInstance<UScCondition>);
	scObjectNameList.Add(TEXT("when"), &createScInstance<UScWhenCondition>);
	scObjectNameList.Add(TEXT("buff"), &createScInstance<UScBuff>);
	scObjectNameList.Add(TEXT("foreach"), &createScInstance<UScForEach>);

	//Flill bcObjectList
	bcObjectNameList.Add(TEXT("heal"), &createBcInstance<UBcHeal>);
	bcObjectNameList.Add(TEXT("when"), &createBcInstance<UBcWhenCondition>);
	bcObjectNameList.Add(TEXT("foreach"), &createBcInstance<UBcForEach>);
	//scObjectNameList.Add(TEXT("heal"), &createScInstance<UScHeal>);
}

XMLSkillReader::~XMLSkillReader()
{
}


TArray<USkill*> XMLSkillReader::ReadXmlSkillFile(FString path)
{
	FString projectDir = FPaths::GameDir();
	FXmlFile* file = new FXmlFile();
	projectDir += path;
	file->LoadFile(projectDir, EConstructMethod::ConstructFromFile);

	// get Root node
	auto pRoot = file->GetRootNode();
	
	return readeSkillsFromXml(pRoot);
}


TArray<UBaseSkillComponent*> XMLSkillReader::createImpact(FXmlNode* impactNode)
{
	TArray<UBaseSkillComponent*> skillComponentList;
	TArray<FXmlNode*> objList = impactNode->GetChildrenNodes();
	for (auto& obj : objList)
	{
		FString tagName = obj->GetTag();

		if (scObjectNameList.Contains(tagName))
		{
			classFuncPtr createFunc = *(scObjectNameList.Find(tagName));
			UBaseSkillComponent* sc = createFunc();
			sc->init(obj);
			sc->SkillName = currentSkillName;
			skillComponentList.Add(sc);
		}
	}
	return skillComponentList;
}

TArray<USkill*> XMLSkillReader::readeSkillsFromXml(FXmlNode* node)
{
	ProfessionName profession;
	TArray<USkill*> SkillObjList;
	TArray<FXmlNode*> propertyList = node->GetChildrenNodes();
	for (auto& prop : propertyList)
	{
		profession = SkillEnums::stringToProfessionName(prop->GetAttribute(TEXT("value")));
		TArray<FXmlNode*> skillList = prop->GetChildrenNodes();
		for (auto& skillNode : skillList)
		{
			SkillObjList.Add(ReadSkill(skillNode));
		}

	}
	return SkillObjList;
}



USkill* XMLSkillReader::ReadSkill(FXmlNode* skillRootNode)
{
	//attribute names
	FString value = FString(TEXT("value"));
	FString scaling = FString(TEXT("scaling"));
	FString type = FString(TEXT("type"));
	FString key = FString(TEXT("key"));

	//values needed for Skill creation
	USkill* skill = NewObject<USkill>();
	skill->skillType = SkillEnums::stringToSkillType(skillRootNode->GetAttribute(type));
	TArray<UBaseSkillComponent*> componentList;

	TArray<FXmlNode*> propertyList = skillRootNode->GetChildrenNodes();
	for (auto& prop : propertyList)
	{
		FString tagName = prop->GetTag();
		if (tagName.Equals(TEXT("name")))
		{
			skill->name = prop->GetAttribute(value);
			currentSkillName = prop->GetAttribute(value);
		}

		else if (tagName.Equals(TEXT("costs")))
		{
			skill->manaCost = FCString::Atoi(*(prop->GetAttribute(value)));
		}

		else if(tagName.Equals(TEXT("casttime")))
		{
			skill->castTime = FCString::Atof(*(prop->GetAttribute(value)));
		}

		else if(tagName.Equals(TEXT("cooldown")))
		{
			skill->recharge = FCString::Atoi(*(prop->GetAttribute(value)));
		}

		else if(tagName.Equals(TEXT("targettype")))
		{
			skill->targetType = SkillEnums::stringToTargetType(prop->GetAttribute(value));
		}
		else if (tagName.Equals(TEXT("range")))
		{
			skill->range = FCString::Atoi(*(prop->GetAttribute(value)));
		}

		else if(tagName.Equals(TEXT("effects")))
		{
			FXmlNode* impactNode = prop->GetChildrenNodes()[0];
			skill->componentList = createImpact(impactNode);
		}

		
	}

	return skill;
}
