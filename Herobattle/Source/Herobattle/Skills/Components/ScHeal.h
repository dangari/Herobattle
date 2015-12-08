#pragma once
#include "BaseSkillComponent.h"
#include "ScHeal.generated.h"

UCLASS()
class  HEROBATTLE_API UScHeal : public UBaseSkillComponent
{
	GENERATED_BODY()
public:
	ComponentTarget targetType;
	UScHeal();
	~UScHeal();
	virtual bool run(ABaseCharacter* target, ABaseCharacter* self) override;
	virtual float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore) override;

	virtual void init(FXmlNode* node) override;

};

