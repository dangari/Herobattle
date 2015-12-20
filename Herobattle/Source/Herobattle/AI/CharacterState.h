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
	FWeaponValues weapon;

	FVector location;
	float airDistance;
	float walkDistance;

	bool isCasting = false;
	bool isAutoAttacking = false;
	bool isBuffed = false;
	bool isHexed = false;
	bool hasStance = false;
	
	TArray<Condition> conditions;

	float health;

	FSkillStatus skillState;

	ABaseCharacter* selectedTarget;
	ABaseCharacter* self;

	float DeltaTime;

	HBCharacterState state;

};