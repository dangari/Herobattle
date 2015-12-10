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

//
//bool UScForEach::run(ABaseCharacter* target, ABaseCharacter* self)
//{
//	bool b = true;
//	uint8 count = 0;
//	if (skillType.Equals(TEXT("CONDITION")))
//	{
//		count = target->getCondtionCount();
//	}
//	if (count > 0){
//		for (int i = 1; i <= count; i++)
//		{
//			for (auto& scObj : scList)
//			{
//				b= scObj->run(target, self);
//			}
//		}
//	}
//	return b;
//}
//
//void UScForEach::init(FXmlNode* node)
//{
//	skillType = node->GetAttribute(TEXT("type"));
//	TArray<FXmlNode*> childNodes = node->GetChildrenNodes();
//	for (auto& scObj : childNodes)
//	{
//		FString tagName = scObj->GetTag();
//		if (XMLSkillReader::scObjectNameList.Contains(tagName))
//		{
//			classFuncPtr createFunc = *(XMLSkillReader::scObjectNameList.Find(tagName));
//			UBaseSkillComponent* sc = createFunc();
//			sc->init(scObj);
//			scList.Add(sc);
//		}
//	}
//}
//
//float UScForEach::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
//{
//	return 0.f;
//}

