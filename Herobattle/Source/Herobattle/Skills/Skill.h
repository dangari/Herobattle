#pragma once

#include "../Enum/SkillEnums.h"
#include "AI/CharacterState.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
	FString name;
	ProfessionName profession;
	TargetType targetType;
	SkillType skillType;
	CostType costType;


	float castTime;
	float recharge;
	float currentRecharge;
	int manaCost;

	UPROPERTY(Replicated)
	TArray<UBaseSkillComponent*> componentList;
	int32 range;
	bool run(ABaseCharacter* target, ABaseCharacter* self);
	bool isValidTarget(ABaseCharacter* target, ABaseCharacter* self);

	float getScore(ABaseCharacter* caster, FCharacterState charcterState);


	UFUNCTION(BlueprintCallable, Category = Debug)
	FString ToString();


private: 
	float manaScore(ABaseCharacter* caster, FCharacterState charcterState);
};
