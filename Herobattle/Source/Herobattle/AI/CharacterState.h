#pragma once

#include "CharacterState.generated.h"

USTRUCT()
struct FCharacterState
{
	GENERATED_USTRUCT_BODY()

	FVector location;
	float airDistance;
	float walkDistance;
	bool isCasting;
	bool isAutoAttacking;


};