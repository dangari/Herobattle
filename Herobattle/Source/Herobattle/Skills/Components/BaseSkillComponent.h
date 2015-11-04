#pragma once

#include "../../Enum/SkillEnums.h"
#include "BaseSkillComponent.generated.h"


class ABaseCharacter;
class FXmlNode;


UCLASS()
class  HEROBATTLE_API UBaseSkillComponent : public UObject
{
	GENERATED_BODY()
//Parameters
public:
	int scaleTable[20];
	Attributes scaleAttribute;
private:
// Functions
public:
	UBaseSkillComponent();
	~UBaseSkillComponent();

	virtual void run(ABaseCharacter* target, ABaseCharacter* self);
	virtual float getScore();
	virtual void init(FXmlNode* node);

private:
	//asdjas
};

