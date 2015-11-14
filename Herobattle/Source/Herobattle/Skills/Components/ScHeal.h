#pragma once
#include "BaseSkillComponent.h"
#include "ScHeal.generated.h"

UCLASS()
class  HEROBATTLE_API UScHeal : public UBaseSkillComponent
{
	GENERATED_BODY()
public:
	UScHeal();
	~UScHeal();
	virtual bool run(ABaseCharacter* target, ABaseCharacter* self) override;
	virtual float getScore() override;

	virtual void init(FXmlNode* node) override;

};

