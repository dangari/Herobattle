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
	ABaseCharacter* testTarget = getTarget(target, self);

	if ((testTarget->selectedTarget == self || targetType == ComponentTarget::SELF) && (target->getState() != HBCharacterState::IDLE) || target->getState() != HBCharacterState::MOVEING)
	{
		if (testTarget->getState() == HBCharacterState::AUTOATTACK &&
			sType == SkillType::ATTACK)
		{
			return true;
		}
		else
		{
			return false;
		}
		if (testTarget->getState() == HBCharacterState::CASTING)
		{
			SkillType characterSkillType = testTarget->getCurrentSkillType();
			if (sType == characterSkillType)
				return true;
			else if (sType == SkillType::ATTACK && (characterSkillType == SkillType::MELEEATTACK || characterSkillType == SkillType::RANGEATTACK))
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

}

void UBoolAttack::init(FXmlNode* node, ComponentTarget target)
{
	targetType = target;
	TArray<FXmlNode*> propertyList = node->GetChildrenNodes();
	
	name = node->GetTag();
	if (name.Equals(TEXT("attack")))
	{
		sType = SkillEnums::stringToSkillType(node->GetAttribute(TEXT("type")));
	}

}