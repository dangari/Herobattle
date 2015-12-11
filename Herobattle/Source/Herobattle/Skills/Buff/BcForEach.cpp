// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BcForEach.h"
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
	if (skillType.Equals(TEXT("CONDITION")))
	{
		count = self->getCondtionCount();
	}
	if (count > 0){
		for (int i = 1; i <= count; i++)
		{
			for (auto& scObj : scList)
			{
				b = scObj->run(self, self);
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

void UBcForEach::init(FBuffContainer bContainer, ABaseCharacter* owner)
{
	FXmlNode* node = bContainer.node;
	skillType = node->GetAttribute(TEXT("type"));
	TArray<FXmlNode*> childNodes = node->GetChildrenNodes();
	for (auto& scObj : childNodes)
	{
		FString tagName = scObj->GetTag();
		if (XMLSkillReader::scObjectNameList.Contains(tagName))
		{
			classFuncPtr createFunc = *(XMLSkillReader::scObjectNameList.Find(tagName));
			UBaseSkillComponent* sc = createFunc();
			sc->init(scObj);
			scList.Add(sc);
		}
	}
}
//
//float UScForEach::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
//{
//	return 0.f;
//}

void UBcForEach::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UBcForEach, scList);
}
