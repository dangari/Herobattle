#pragma once



#include "SkillContainer.generated.h"



class ABaseCharacter;
class USkill;

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
	

	FSkillStatus copy();

	void registerSkill(USkill* skill, ABaseCharacter* target, int32 slot);
};