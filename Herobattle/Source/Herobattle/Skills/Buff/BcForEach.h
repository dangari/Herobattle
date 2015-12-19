// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Components/BaseSkillComponent.h"
#include "BcForEach.generated.h"


/**
 * 
 */
UCLASS()
class HEROBATTLE_API UBcForEach  : public UBaseBuffCompenent
{
	GENERATED_BODY()
public:

	UBcForEach();
	~UBcForEach();


	virtual void init(FBuffContainer bContainer, ABaseCharacter* owner, FSkillProperties properties) override;


	virtual bool run(ABaseCharacter* caster, ABaseCharacter* self, int value = 0) override;

	virtual bool isExpired() override;

	virtual void update(float deltaTime) override;
	
private:
	FString skillType;

	UPROPERTY(Replicated)
	TArray<UBaseBuffCompenent*> bcList;
};
