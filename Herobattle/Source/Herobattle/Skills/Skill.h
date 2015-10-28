#pragma once

#include "../Enum/SkillEnums.h"
#include "Skill.generated.h"




/**
 * 
 */

// Damage 
UCLASS()
class HEROBATTLE_API USkill : public UObject
{
	GENERATED_BODY()
public:
	USkill();
	~USkill();

private:
	//string name;
	ProfessionName profession;
	float castTime;
	float recharge;
	float currentRecharge;
	int manaCost;

};
