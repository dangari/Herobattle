// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "ScAdrenaline.h"




UScAdrenaline::UScAdrenaline()
{
	componentName = TEXT("adrenaline");
}

UScAdrenaline::~UScAdrenaline()
{

}

bool UScAdrenaline::run(ABaseCharacter* target, ABaseCharacter* self, FString SkillName /*= TEXT("Name")*/)
{
	ABaseCharacter* newTarget = getTarget(target, self);
	int value = scaleTable[self->getAttributeValue(Attributes::STRENGTH)];
	newTarget->addAdrenaline(value);
	return true;
	
}

bool UScAdrenaline::runSim(UAISimCharacter* target, UAISimCharacter* self, FString SkillName /*= TEXT("Name")*/)
{
	UAISimCharacter* newTarget = getTargetSim(target, self);
	int value = scaleTable[self->getAttributeValue(Attributes::STRENGTH)];
	newTarget->addAdrenaline(value);
	return true;
}

float UScAdrenaline::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	float score = caster->missingAdrenaline() / scaleTable[caster->getAttributeValue(Attributes::STRENGTH)];
	if (score > 1)
		score = 1;
	skillScore->addScore(score, TEXT("adrenaline"));
	return 1.f;
}

float UScAdrenaline::getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	float score = caster->missingAdrenaline() / scaleTable[caster->getAttributeValue(Attributes::STRENGTH)];
	if (score > 1)
		score = 1;
	skillScore->addScore(score, TEXT("adrenaline"));
	return 1.f;
}

void UScAdrenaline::init(FXmlNode* node, FSkillProperties properties)
{
	Super::init(node, properties);
	targetType = SkillEnums::stringToComponentTarget(node->GetAttribute("target"));
	FString tagName = node->GetTag();
	if (tagName.Equals(TEXT("giveadrenaline")))
	{
		fillScaleTable(node);
	}
}

FString UScAdrenaline::ToString()
{
	return TEXT("adrenaline");
}
