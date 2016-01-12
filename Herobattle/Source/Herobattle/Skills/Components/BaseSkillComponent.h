#pragma once

#include "../../Enum/SkillEnums.h"
#include "XmlParser.h"
#include "AI/CharacterState.h"
#include "../Skill.h"
#include "BaseSkillComponent.generated.h"


class USkillScore;
class ABaseCharacter;
class UAISimCharacter;



UCLASS()
class  HEROBATTLE_API UBaseSkillComponent : public UObject
{
	GENERATED_BODY()
//Parameters
public:


public:
	UBaseSkillComponent();
	~UBaseSkillComponent();

	virtual bool run(ABaseCharacter* target, ABaseCharacter* self, FString SkillName = TEXT("Name"));
	virtual bool runSim(UAISimCharacter* target, UAISimCharacter* self, FString SkillName = TEXT("Name"));


	virtual float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore);
	virtual float getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore);

	virtual void init(FXmlNode* node, FSkillProperties properties);
	virtual FString ToString();

	static UBaseSkillComponent* UBaseSkillComponent::MAKE();

	FString SkillName;
	int scaleTable[20];
	Attributes scaleAttribute;

protected:
	void fillScaleTable(FXmlNode* node);

	ABaseCharacter* getTarget(ABaseCharacter* target, ABaseCharacter* self);
	UAISimCharacter* getTargetSim(UAISimCharacter* target, UAISimCharacter* self);

	FString componentName;

	ComponentTarget targetType;

	FSkillProperties m_properties;
};

