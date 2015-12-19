// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Buff/BaseBuffCompenent.h"
#include "BcHeal.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UBcHeal : public UBaseBuffCompenent
{
	GENERATED_BODY()
	
public:
	int heal;
	UBcHeal();
	~UBcHeal();

	virtual void init(FBuffContainer bContainer, ABaseCharacter* owner, FSkillProperties properties) override;

	
	virtual bool run(ABaseCharacter* caster, ABaseCharacter* self, int value = 0) override;

	virtual bool isExpired() override;
	
	virtual void update(float deltaTime) override;

private:
	Trigger trigger;

	
};
