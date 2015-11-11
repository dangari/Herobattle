// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "XMLSkillReader.h"
#include "XmlParser.h"
#include "Engine.h"
#include "Skill.h"
#include "Components/BaseSkillComponent.h"
#include "Components/ScHeal.h"
#include "Components/ScDamage.h"
#include "Components/ScCondition.h"
#include "Components/ScWhenCondition.h"


TMap<FString, classFuncPtr> XMLSkillReader::scObjectNameList;


XMLSkillReader::XMLSkillReader()
{

	//Fill scObjectNameList
	scObjectNameList.Add(TEXT("damage"), &createInstance<UScDamage>);
	scObjectNameList.Add(TEXT("heal"), &createInstance<UScHeal>);
	scObjectNameList.Add(TEXT("condition"), &createInstance<UScCondition>);
	scObjectNameList.Add(TEXT("whencondition"), &createInstance<UScWhenCondition>);

	// loading file
	FString projectDir = FPaths::GameDir();
	FXmlFile* file = new FXmlFile();
	projectDir += "Source/Herobattle/Definitions/skill.xml";
	file->LoadFile(projectDir, EConstructMethod::ConstructFromFile);

	// get Root node
	auto pRoot = file->GetRootNode();

	readeSkillsFromXml(pRoot);
	TArray<FXmlNode*> propertyList = pRoot->GetChildrenNodes();
	FXmlNode* temp = propertyList[0];
	FXmlNode* temp2 = temp->GetChildrenNodes()[0];
	ReadSkill(temp2);
	FString pChild = pRoot->GetTag();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, pChild);
}

XMLSkillReader::~XMLSkillReader()
{
}


USkill* XMLSkillReader::ReadXmlSkillFile(FString path)
{
	return nullptr;
}

TargetType XMLSkillReader::getTargetTypeFromString(FString name)
{
	if (name.Equals(TEXT("ENEMY")))
	{
		return TargetType::ENEMY;
	}
	if (name.Equals(TEXT("SELF")))
	{
		return TargetType::SELF;
	}
	if (name.Equals(TEXT("FRIEND")))
	{
		return TargetType::FRIEND;
	}
	if (name.Equals(TEXT("SELFFREND")))
	{
		return TargetType::SELFFREND;
	}
	return TargetType::ENEMY;
}

TArray<UBaseSkillComponent*> XMLSkillReader::createImpact(FXmlNode* impactNode)
{
	TArray<UBaseSkillComponent*> skillComponentList;
	TArray<FXmlNode*> objList = impactNode->GetChildrenNodes();
	for (auto& obj : objList)
	{
		FString tagName = obj->GetTag();
		if (tagName.Equals(TEXT("damage")))
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, tagName);
		if (scObjectNameList.Contains(tagName))
		{
			classFuncPtr createFunc = *(scObjectNameList.Find(tagName));
			UBaseSkillComponent* sc = createFunc();
			sc->init(obj);
			skillComponentList.Add(sc);
		}
	}
	return skillComponentList;
}

void XMLSkillReader::readeSkillsFromXml(FXmlNode* node)
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
}



USkill* XMLSkillReader::ReadSkill(FXmlNode* skillRootNode)
{
	//attribute names
	FString value = FString(TEXT("value"));
	FString scaling = FString(TEXT("scaling"));
	FString type = FString(TEXT("type"));
	FString key = FString(TEXT("key"));

	//values needed for Skill creation
	FString name;
	int costs;
	int cooldown;
	float castTime;
	TargetType targetType;

	TArray<UBaseSkillComponent*> componentList;

	TArray<FXmlNode*> propertyList = skillRootNode->GetChildrenNodes();
	for (auto& prop : propertyList)
	{
		FString tagName = prop->GetTag();
		if (tagName.Equals(TEXT("name")))
		{
			name = prop->GetAttribute(value);
		}

		if (tagName.Equals(TEXT("costs")))
		{
			costs = FCString::Atoi(*(prop->GetAttribute(value)));
		}

		if (tagName.Equals(TEXT("casttime")))
		{
			castTime = FCString::Atof(*(prop->GetAttribute(value)));
		}

		if (tagName.Equals(TEXT("cooldown")))
		{
			cooldown = FCString::Atoi(*(prop->GetAttribute(value)));
		}

		if (tagName.Equals(TEXT("targettype")))
		{
			targetType = getTargetTypeFromString(prop->GetAttribute(value));
		}

		if (tagName.Equals(TEXT("effects")))
		{
			FXmlNode* impactNode = prop->GetChildrenNodes()[0];
			componentList = createImpact(impactNode);
		}

		
	}
	USkill* skill = NewObject<USkill>();
	skill->name = name;
	skill->castTime = castTime;
	skill->recharge = cooldown;
	skill->manaCost = costs;
	skill->targetType = targetType;
	skill->componentList = componentList;

	return skill;
}
