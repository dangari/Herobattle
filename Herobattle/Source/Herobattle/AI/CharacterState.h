#pragma once

#include "Base/SkillContainer.h"
#include "Enum/SkillEnums.h"
#include "Enum/CharacterEnums.h"
#include "Base/Weapon.h"
#include "CharacterState.generated.h"



class ABaseCharacter;
class UAISimCharacter;

USTRUCT()
struct FCharacterState
{
	GENERATED_USTRUCT_BODY()

	FString name;

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
	UAISimCharacter* selectedTargetSim;
	ABaseCharacter* self;
	UAISimCharacter* selfSim;

	float DeltaTime;

	HBCharacterState state;

	int attackers;
	int caster;

	SkillType skillType;

	TMap<Attributes, uint8 > attrList;

	

	inline bool operator==(const FCharacterState& Other) const
	{
		return name.Equals(Other.name);
	}

};