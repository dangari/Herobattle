// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "ScRegeneratio.h"
#include "Base/BaseCharacter.h"
#include "AI/SkillScore.h"



UScRegeneratio::UScRegeneratio()
{
	componentName = TEXT("Regeneration");
}

UScRegeneratio::~UScRegeneratio()
{

}

bool UScRegeneratio::run(ABaseCharacter* target, ABaseCharacter* self, FString SkillName /*= TEXT("Name")*/)
{
	//target->updateHealthRegen(scaleTable[self->getAttributeValue(scaleAttribute)]);
	return true;
}

void UScRegeneratio::init(FXmlNode* node)
{
	TArray<FXmlNode*> propertyList = node->GetChildrenNodes();
	FString tagName = node->GetTag();
	if (tagName.Equals(TEXT("regeneration")))
	{
		fillScaleTable(node);
	}
}

float UScRegeneratio::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	return 0.f;
}
