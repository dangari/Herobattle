#pragma once

#include "../Enum/SkillEnums.h"
#include "Skill.generated.h"



class UBaseSkillComponent;
class ABaseCharacter;
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

	UPROPERTY(Replicated)
	TArray<UBaseSkillComponent*> componentList;
	int32 range;
	bool run(ABaseCharacter* target, ABaseCharacter* self);
	bool isValidTarget(ABaseCharacter* target, ABaseCharacter* self);

};
