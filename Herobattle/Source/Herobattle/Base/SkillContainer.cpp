#include "Herobattle.h"
#include "SkillContainer.h"
#include "BaseCharacter.h"
#include "Skills/Skill.h"


FSkillStatus FSkillStatus::copy()
{
	FSkillStatus newSkillStatus;
	newSkillStatus.skillName = this->skillName;
	newSkillStatus.leftCastTime = this->leftCastTime;
	newSkillStatus.castTime = this->castTime;
	newSkillStatus.skill = this->skill;
	newSkillStatus.target = this->target;
	newSkillStatus.slot = this->slot;
	newSkillStatus.castingSkill = this->castingSkill;
	return newSkillStatus;
}

void FSkillStatus::registerSkill(USkill* skill, ABaseCharacter* target, int32 slot)
{
	castingSkill = true;
	this->skill = skill;
	leftCastTime = skill->properties.castTime;
	skillName = skill->properties.name;
	this->target = target;
	this->slot = slot;
	castTime = skill->properties.castTime;
}