#pragma once

UENUM(BlueprintType)
enum class TeamColor : uint8
{
	RED, BLUE
};

UENUM(BlueprintType)
enum class HBCharacterState : uint8
{
	MOVEING, IDLE, AUTOATTACK, CASTING
};
