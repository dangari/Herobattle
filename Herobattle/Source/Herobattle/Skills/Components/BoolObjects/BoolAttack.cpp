// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BoolAttack.h"
#include "../../../Base/BaseCharacter.h"
#include "Base/Weapon.h"
#include "Enum/CharacterEnums.h"


UBoolAttack::UBoolAttack()
{
}

UBoolAttack::~UBoolAttack()
{
}

bool UBoolAttack::test(ABaseCharacter* target, ABaseCharacter* self)
{
	bool test = false;
	ABaseCharacter* testTarget = getTarget(target, self);

	if (target->selectedTarget == self && (target->getState() != HBCharacterState::IDLE) || target->getState() != HBCharacterState::MOVEING)
	{
		if (target->getState() == HBCharacterState::AUTOATTACK &&
			sType == SkillType::ATTACK)
		{
			return true;
		}
		else
		{
			return false;
		}
		if (target->getState() == HBCharacterState::CASTING)
		{
			SkillType characterSkillType = target->getCurrentSkillType();
			if (sType == characterSkillType)
				return true;
			else
				return false;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return test;
}

void UBoolAttack::init(FXmlNode* node, ComponentTarget target)
{
	targetType = target;
	TArray<FXmlNode*> propertyList = node->GetChildrenNodes();
	
	FString tagName = node->GetTag();
	if (tagName.Equals(TEXT("attack")))
	{
		sType = SkillEnums::stringToSkillType(node->GetAttribute(TEXT("type")));
	}

}