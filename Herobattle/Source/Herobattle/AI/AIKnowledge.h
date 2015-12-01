 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTService.h"
#include "AIKnowledge.generated.h"

/**
 * 
 */
class UNavigationSystem;
class ABaseCharacter;

UCLASS()
class HEROBATTLE_API UAIKnowledge : public UBTService
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = Properties)
	int32 fRange = 30000;

	UAIKnowledge();
	~UAIKnowledge();

	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	virtual void SetOwner(AActor* ActorOwner) override;

private:
	UNavigationSystem* m_NavSys;
	ABaseCharacter* owner;
	
};
