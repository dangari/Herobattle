// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "BaseBuffCompenent.generated.h"

/**
 * 
 */

class ABaseCharacter;
class FXmlNode;

UCLASS()
class HEROBATTLE_API UBaseBuffCompenent : public UObject
{
	GENERATED_BODY()
	
public:

	virtual void init(FXmlNode* node, ABaseCharacter* owner);
	// runs the buff
	virtual bool run(ABaseCharacter* caster, ABaseCharacter* self, int value);
	virtual bool isExpired();
	
protected:
	ABaseCharacter* owner;
	int usage;
};
