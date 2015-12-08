// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Components/BaseSkillComponent.h"
#include "../../Enum/SkillEnums.h"
#include "ScDamage.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UScDamage : public UBaseSkillComponent
{
	GENERATED_BODY()
public:
	UScDamage();
	~UScDamage();
	virtual bool run(ABaseCharacter* target, ABaseCharacter* self) override;
	virtual float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore) override;

	virtual void init(FXmlNode* node) override;

	virtual FString ToString() override;

	HBDamageType damageType;
	ComponentTarget targetType;
private:

};
