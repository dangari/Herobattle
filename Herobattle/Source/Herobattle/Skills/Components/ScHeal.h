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
	virtual bool run(ABaseCharacter* target, ABaseCharacter* self, FString SkillName = TEXT("Name")) override;
	virtual bool runSim(UAISimCharacter* target, UAISimCharacter* self, FString SkillName = TEXT("Name")) override;

	virtual float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore) override;
	virtual float getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore) override;

	virtual void init(FXmlNode* node, FSkillProperties properties) override;

	virtual FString ToString() override;

};

