#pragma once

#include "../../Enum/SkillEnums.h"
#include "Skills/Components/BaseSkillComponent.h"
#include "ScCondition.generated.h"


class ABaseCharacter;



UCLASS()
class  HEROBATTLE_API UScCondition : public UBaseSkillComponent
{
	GENERATED_BODY()
//Parameters
public:

	Condition conditionType;
	TargetType targetType;
private:
// Functions
public:
	UScCondition();
	~UScCondition();

	virtual bool run(ABaseCharacter* target, ABaseCharacter* self, FString SkillName = TEXT("Name")) override;
	virtual float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore) override;

	virtual void init(FXmlNode* node) override;

	virtual FString ToString() override;

private:
	//asdjas
	
};

