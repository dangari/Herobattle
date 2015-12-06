#pragma once

#include "Base/SkillContainer.h"
#include "Enum/SkillEnums.h"
#include "Enum/CharacterEnums.h"
#include "Base/Weapon.h"
#include "CharacterState.generated.h"



class ABaseCharacter;

USTRUCT()
struct FCharacterState
{
	GENERATED_USTRUCT_BODY()

	TeamColor ETeam;
	FWeapon weapon;

	FVector location;
	float airDistance;
	float walkDistance;

	bool isCasting = false;
	bool isAutoAttacking = false;
	bool isBuffed = false;
	bool isHexed = false;
	
	TArray<Condition> conditions;

	float health;

	FSkillStatus skillState;

	ABaseCharacter* selectedTarget;
	ABaseCharacter* self;

};