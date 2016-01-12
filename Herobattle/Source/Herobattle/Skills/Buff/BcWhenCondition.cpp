// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BcWhenCondition.h"
#include "../Components/BoolObjects/BoolObject.h"
#include "../Components/BoolObjects/BoolHealth.h"
#include "../XMLSkillReader.h"
#include "UnrealNetwork.h"
#include "AI/SkillScore.h"
#include "../Components/BaseSkillComponent.h"
#include "../Components/BoolObjects/BoolAttack.h"
#include "../Components/BoolObjects/BoolCondition.h"
#include "../Components/BoolObjects/BoolHex.h"

UBcWhenCondition::UBcWhenCondition()
{

}


UBcWhenCondition::~UBcWhenCondition()
{
}




bool UBcWhenCondition::testConditions(ABaseCharacter* target, ABaseCharacter* self)
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

void UBcWhenCondition::init(FBuffContainer bContainer, ABaseCharacter* owner, FSkillProperties properties)
{
	Super::init(bContainer, owner, properties);
	FXmlNode* node = bContainer.node;
	FString cType = node->GetAttribute(TEXT("type"));
	targetType = SkillEnums::stringToComponentTarget(cType);
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
			createSkillComponents(prop, properties);
		}
	}
}

void UBcWhenCondition::initSim(FBuffContainer bContainer, UAISimCharacter* owner, FSkillProperties properties)
{
	Super::initSim(bContainer, owner, properties);
	FXmlNode* node = bContainer.node;
	FString cType = node->GetAttribute(TEXT("type"));
	targetType = SkillEnums::stringToComponentTarget(cType);
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
			createSkillComponents(prop, properties);
		}
	}
}

bool UBcWhenCondition::run(ABaseCharacter* caster, ABaseCharacter* self, int value)
{
	return true;
}

bool UBcWhenCondition::runSim(UAISimCharacter* caster, UAISimCharacter* self, int value /*= 0*/)
{
	return true;
}

bool UBcWhenCondition::isExpired()
{
	return false;
}

void UBcWhenCondition::update(float deltaTime)
{

}

float UBcWhenCondition::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{
	return 1.f;
}

float UBcWhenCondition::getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{
	return 1.f;
}

void UBcWhenCondition::createBoolObjects(FXmlNode* node)
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
		else if (tagName.Equals(TEXT("attack")))
		{
			UBoolAttack* attackBool = NewObject<UBoolAttack>();
			attackBool->init(prop, targetType);
			boolObjects.Add(attackBool);
		}
		else if (tagName.Equals(TEXT("condi")))
		{
			UBoolCondition* attackCondition = NewObject<UBoolCondition>();
			attackCondition->init(prop, targetType);
			boolObjects.Add(attackCondition);
		}
		else if (tagName.Equals(TEXT("hex")))
		{
			UBoolHex* attackCondition = NewObject<UBoolHex>();
			attackCondition->init(prop, targetType);
			boolObjects.Add(attackCondition);
		}

	}
}

void UBcWhenCondition::createSkillComponents(FXmlNode* node, FSkillProperties properties)
{
	TArray<FXmlNode*> boolObjectList = node->GetChildrenNodes();
	for (auto& prop : boolObjectList)
	{
		FString tagName = prop->GetTag();
		if (XMLSkillReader::scObjectNameList.Contains(tagName))
		{
			classFuncPtr createFunc = *(XMLSkillReader::scObjectNameList.Find(tagName));
			UBaseSkillComponent* sc = createFunc();
			sc->init(prop, properties);
			scTable.Add(sc);
		}
	}
}


void UBcWhenCondition::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UBcWhenCondition, boolObjects);
	DOREPLIFETIME(UBcWhenCondition, scTable);
}
