#pragma once

#include "../Enum/SkillEnums.h"
#include "Skill.generated.h"



class UBaseSkillComponent;
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

	FString name;
	ProfessionName profession;
	TargetType targetType;
	float castTime;
	float recharge;
	float currentRecharge;
	int manaCost;

	TArray<UBaseSkillComponent*> componentList;

};
