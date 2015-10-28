#pragma once

#include "../../Enum/SkillEnums.h"
#include "ScDurationTypes.generated.h"


class ABaseCharacter;



UCLASS()
class  HEROBATTLE_API UScCondition : public UObject
{
	GENERATED_BODY()
//Parameters
public:
	int scaleTable[20];
	Attributes scaleAttribute;

	Condition conditionType;
private:
// Functions
public:
	UScCondition();
	~UScCondition();

	virtual void run(ABaseCharacter* target, ABaseCharacter* self);
	virtual float getScore();

private:
	//asdjas
};

