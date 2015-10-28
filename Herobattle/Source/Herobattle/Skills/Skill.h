#pragma once

#include "Skill.generated.h"



/**
 * 
 */
UENUM(BlueprintType)
enum class ProfessionName : uint8{ ASSASINE, ELEMENTALIST, MONK, DERWISH, NEKROMANT, PARAGON, WARRIOR, MESMER, RITUALIST };
UENUM(BlueprintType)
enum class SkillType : uint8{ ENTCHANTMENT, ATTACK, HEX, SPELL, HEAL };
UENUM(BlueprintType)
enum class TargetType : uint8{ SELF, ENEMY, FRIEND, SELFFREND };
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
