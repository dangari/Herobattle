#pragma once

#include "Skills/Skill.h"
#include "SkillContainer.generated.h"




USTRUCT()
struct FSkillHUD
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skills)
	FString skillName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skills)
		float leftCastTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skills)
		float castTime;
};

USTRUCT()
struct FSkillStatus
{
	GENERATED_USTRUCT_BODY()

	


	UPROPERTY()
		FString skillName;
	UPROPERTY()
		float leftCastTime;
	UPROPERTY()
		float castTime;
	UPROPERTY()
		USkill* skill;
	UPROPERTY()
		ABaseCharacter* target;
	UPROPERTY()
		int32 slot;

	UPROPERTY()
		bool castingSkill = false;
	
	FSkillStatus()
	{
		castingSkill = false;
	}

	FSkillStatus copy()
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

	void registerSkill(USkill* skill, ABaseCharacter* target, int32 slot)
	{
		castingSkill = true;
		this->skill = skill;
		leftCastTime = skill->castTime;
		skillName = skill->name;
		this->target = target;
		this->slot = slot;
		castTime = skill->castTime;
	}
};