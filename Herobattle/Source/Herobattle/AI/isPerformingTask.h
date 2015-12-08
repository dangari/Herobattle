// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "isPerformingTask.generated.h"

class ABaseCharacter;
class AAIController;

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UisPerformingTask : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UisPerformingTask();
	~UisPerformingTask();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override final;
	virtual void SetOwner(AActor* ActorOwner) override;
	

private:
	ABaseCharacter* m_owner;
	AAIController* AIOwnerController;
};
