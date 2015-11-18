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
	scObjectNameList.Add(TEXT("when"), &createInstance<UScWhenCondition>);

	// loading file
	//FString projectDir = FPaths::GameDir();
	//FXmlFile* file = new FXmlFile();
	//projectDir += "Source/Herobattle/Definitions/skill.xml";
	//file->LoadFile(projectDir, EConstructMethod::ConstructFromFile);

	//// get Root node
	//auto pRoot = file->GetRootNode();

	//readeSkillsFromXml(pRoot);
	//TArray<FXmlNode*> propertyList = pRoot->GetChildrenNodes();
	//FXmlNode* temp = propertyList[0];
	//FXmlNode* temp2 = temp->GetChildrenNodes()[0];
	//ReadSkill(temp2);
	//FString pChild = pRoot->GetTag();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, pChild);
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

	TArray<UBaseSkillComponent*> componentList;

	TArray<FXmlNode*> propertyList = skillRootNode->GetChildrenNodes();
	for (auto& prop : propertyList)
	{
		FString tagName = prop->GetTag();
		if (tagName.Equals(TEXT("name")))
		{
			skill->name = prop->GetAttribute(value);
			
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

		else if(tagName.Equals(TEXT("effects")))
		{
			FXmlNode* impactNode = prop->GetChildrenNodes()[0];
			skill->componentList = createImpact(impactNode);
		}

		
	}

	return skill;
}
