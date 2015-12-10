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
	

	virtual void init(FBuffContainer bContainer, ABaseCharacter* owner) override;


	virtual bool run(ABaseCharacter* caster, ABaseCharacter* self, int value) override;

	virtual bool isExpired() override;

	virtual void update(float deltaTime) override;

private:

	UPROPERTY(Replicated)
	TArray<UBaseSkillComponent*> scTable; // components that gets executed when condition is true
	UPROPERTY(Replicated)
	TArray<UBoolObject*> boolObjects;
	ComponentTarget targetType;
	bool testConditions(ABaseCharacter* target, ABaseCharacter* self);


	void createBoolObjects(FXmlNode* node);
	
	void createSkillComponents(FXmlNode* node);

};
