// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "XMLSkillReader.h"
#include "XmlParser.h"
#include "Engine.h"
#include "Skill.h"
#include "Components/BaseSkillComponent.h"
#include "Components/ScHeal.h"
#include "Components/ScDamage.h"



XMLSkillReader::XMLSkillReader()
{

	//Fill scObjectNameList
	scObjectNameList.Add(TEXT("damage"), &createInstance<UScDamage>);
	scObjectNameList.Add(TEXT("heal"), &createInstance<UScHeal>);

	FXmlFile* file = new FXmlFile();
	file->LoadFile(L"F://Herobattle/Herobattle/Source/Herobattle/Definitions/skill.xml", EConstructMethod::ConstructFromFile);
	printf("s",file->GetLastError());
	auto pRoot = file->GetRootNode();
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

UBaseSkillComponent* XMLSkillReader::createImpact(FXmlNode* impactNode)
{

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
		}
	}
	return nullptr;
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
			createImpact(impactNode);
		}
	}
	
	// skill type
	// name
	// costs
	// cast time
	// cool down
	// Target typ
	// impact

	return nullptr;
}