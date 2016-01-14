// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BcForEach.h"
#include "BaseBuffCompenent.h"
#include "Buff.h"
//#include "XmlParser.h"
//#include "../XMLSkillReader.h"
//#include "Base/BaseCharacter.h"
//#include "AI/SkillScore.h"
//
//
//
UBcForEach::UBcForEach()
{

}

UBcForEach::~UBcForEach()
{

}


bool UBcForEach::run(ABaseCharacter* caster, ABaseCharacter* self, int value)
{
	bool b = true;
	uint8 count = 0;
	ABaseCharacter* newTarget = getTarget(caster, self);
	if (skillType.Equals(TEXT("CONDITION")))
	{
		count = newTarget->getCondtionCount();
	}
	else if (skillType.Equals(TEXT("ENCHANTMENT")))
	{
		count = newTarget->getBuffCount();
	}
	UE_LOG(LogTemp, Warning, TEXT("count: %d"), count)
	if (count > 0){
		for (int i = 1; i <= count; i++)
		{
			for (auto& scObj : bcList)
			{
				b = scObj->run(newTarget, newTarget, value);
			}
		}
	}
	return b;
}

bool UBcForEach::runSim(UAISimCharacter* caster, UAISimCharacter* self, int value /*= 0*/)
{
	bool b = true;
	uint8 count = 0;
	UAISimCharacter* newTarget = getTargetSim(caster, self);
	if (skillType.Equals(TEXT("CONDITION")))
	{
		count = newTarget->getCondtionCount();
	}
	else if (skillType.Equals(TEXT("ENCHANTMENT")))
	{
		count = newTarget->getBuffCount();
	}
	UE_LOG(LogTemp, Warning, TEXT("count: %d"), count)
	if (count > 0){
		for (int i = 1; i <= count; i++)
		{
			for (auto& scObj : bcList)
			{
				b = scObj->runSim(newTarget, newTarget, value);
			}
		}
	}
	return b;
}

bool UBcForEach::isExpired()
{
	return false;
}

void UBcForEach::update(float deltaTime)
{

}

float UBcForEach::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{	
	return 1.f;
}

float UBcForEach::getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{
	return 1.f;
}

void UBcForEach::init(FBuffContainer bContainer, ABaseCharacter* owner, FSkillProperties properties, UBuff* ownerBuff)
{
	Super::init(bContainer, owner, properties, ownerBuff);
	FXmlNode* node = bContainer.node;
	skillType = node->GetAttribute(TEXT("type"));
	TArray<FXmlNode*> childNodes = node->GetChildrenNodes();
	targetType = SkillEnums::stringToTargetType(bContainer.node->GetAttribute(TEXT("target")));
	for (auto& bcObj : childNodes)
	{
		FString tagName = bcObj->GetTag();
		if (UBuff::bcObjectNameList.Contains(tagName))
		{
			FBuffContainer buff;
			buff.buffName = tagName;
			buff.targetType = SkillEnums::stringToTargetType(bcObj->GetAttribute(TEXT("target")));
			buff.node = bcObj;
			buff.fillScaleTable(bcObj);

			bCclassFuncPtr createFunc = *(UBuff::bcObjectNameList.Find(tagName));
			UBaseBuffCompenent* bc = createFunc(ownerBuff);
			bc->init(buff, owner, properties, ownerBuff);
			bcList.Add(bc);
		}
	}
}

void UBcForEach::initSim(FBuffContainer bContainer, UAISimCharacter* owner, FSkillProperties properties, UBuff* ownerBuff)
{
	Super::initSim(bContainer, owner, properties, ownerBuff);
	FXmlNode* node = bContainer.node;
	skillType = node->GetAttribute(TEXT("type"));
	TArray<FXmlNode*> childNodes = node->GetChildrenNodes();
	targetType = SkillEnums::stringToTargetType(bContainer.node->GetAttribute(TEXT("target")));
	for (auto& bcObj : childNodes)
	{
		FString tagName = bcObj->GetTag();
		if (UBuff::bcObjectNameList.Contains(tagName))
		{
			FBuffContainer buff;
			buff.buffName = tagName;
			buff.targetType = SkillEnums::stringToTargetType(bcObj->GetAttribute(TEXT("target")));
			buff.node = bcObj;
			buff.fillScaleTable(bcObj);

			bCclassFuncPtr createFunc = *(UBuff::bcObjectNameList.Find(tagName));
			UBaseBuffCompenent* bc = createFunc(this);
			bc->initSim(buff, owner, properties, ownerBuff);
			bcList.Add(bc);
		}
	}
}


void UBcForEach::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UBcForEach, bcList);
}
