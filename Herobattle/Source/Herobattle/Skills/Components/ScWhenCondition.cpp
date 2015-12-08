// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "ScWhenCondition.h"
#include "BoolObjects/BoolObject.h"
#include "BoolObjects/BoolHealth.h"
#include "../XMLSkillReader.h"
#include "UnrealNetwork.h"
#include "AI/SkillScore.h"

UScWhenCondition::UScWhenCondition()
{
	componentName = TEXT("WhenCondition");
}


UScWhenCondition::~UScWhenCondition()
{
}


bool UScWhenCondition::run(ABaseCharacter* target, ABaseCharacter* self)
{
	bool b = true;
	if (testConditions(target, self))
	{
		for (auto& sc : scTable)
		{
			b = sc->run(target, self);
		}
	}
	return b;
}

float UScWhenCondition::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	return 1.f;
}

bool UScWhenCondition::testConditions(ABaseCharacter* target, ABaseCharacter* self)
{
	for (auto& bo : boolObjects)
	{
		if (bo->test(target, self) == false)
		{
			return false;
		}
	}
	return true;
}

void UScWhenCondition::init(FXmlNode* node)
{
	FString cType = node->GetAttribute(TEXT("type"));
	this->targetType = SkillEnums::stringToTargetType(cType);
	TArray<FXmlNode*> propertyList = node->GetChildrenNodes();
	for (auto& prop : propertyList)
	{
		FString tagName = prop->GetTag();
		if (tagName.Equals(TEXT("whencondition")))
		{
			createBoolObjects(prop);
		}
		if (tagName.Equals(TEXT("then")))
		{
			createSkillComponents(prop);
		}
	}
}

void UScWhenCondition::createBoolObjects(FXmlNode* node)
{
	TArray<FXmlNode*> boolObjectList = node->GetChildrenNodes();
	for (auto& prop : boolObjectList)
	{
		FString tagName = prop->GetTag();
		if (tagName.Equals(TEXT("hp")))
		{
			UBoolHealth* hpBool = NewObject<UBoolHealth>();
			hpBool->init(prop, targetType);
			boolObjects.Add(hpBool);
		}
	}
}

void UScWhenCondition::createSkillComponents(FXmlNode* node)
{
	TArray<FXmlNode*> boolObjectList = node->GetChildrenNodes();
	for (auto& prop : boolObjectList)
	{
		FString tagName = prop->GetTag();
		if (XMLSkillReader::scObjectNameList.Contains(tagName))
		{
			classFuncPtr createFunc = *(XMLSkillReader::scObjectNameList.Find(tagName));
			UBaseSkillComponent* sc = createFunc();
			sc->init(prop);
			scTable.Add(sc);
		}
	}
}

FString UScWhenCondition::ToString()
{
	FString sCText = componentName;
	sCText.Append(TEXT(" \n "));
	sCText.Append(Super::ToString());
	for (auto& sC : scTable)
	{
		sCText.Append(TEXT(" \n "));
		sCText.Append(TEXT("\t"));
		sCText.Append(sC->ToString());
	}
	return sCText;
}

void UScWhenCondition::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UScWhenCondition, boolObjects);
	DOREPLIFETIME(UScWhenCondition, scTable);
}
