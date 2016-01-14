// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Components/BaseSkillComponent.h"
#include "Containers/Array.h"
#include "../../Enum/SkillEnums.h"
#include "BuffContainer.h"
#include "BcWhenCondition.generated.h"



class UBoolObject;
class UBaseSkillComponent;

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UBcWhenCondition : public UBaseBuffCompenent
{
	GENERATED_BODY()
public:
	UBcWhenCondition();
	~UBcWhenCondition();
	

	virtual void init(FBuffContainer bContainer, ABaseCharacter* owner, FSkillProperties properties, UBuff* ownerBuff) override;
	virtual void initSim(FBuffContainer bContainer, UAISimCharacter* owner, FSkillProperties properties, UBuff* ownerBuff) override;



	virtual bool run(ABaseCharacter* caster, ABaseCharacter* self, int value = 0) override;
	virtual bool runSim(UAISimCharacter* caster, UAISimCharacter* self, int value = 0) override;


	virtual bool isExpired() override;

	virtual void update(float deltaTime) override;

	virtual float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration) override;
	virtual float getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration) override;



private:
	bool testConditions(ABaseCharacter* target, ABaseCharacter* self);


	void createBoolObjects(FXmlNode* node, UBuff* ownerBuff);

	void createSkillComponents(FXmlNode* node, FSkillProperties properties);


	UPROPERTY(Replicated)
	TArray<UBaseSkillComponent*> scTable; // components that gets executed when condition is true
	UPROPERTY(Replicated)
	TArray<UBoolObject*> boolObjects;
	ComponentTarget targetType;
	

};
