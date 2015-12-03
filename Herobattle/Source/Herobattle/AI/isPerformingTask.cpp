// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "isPerformingTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIGameState.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Base/BaseCharacter.h"




UisPerformingTask::UisPerformingTask()
{

}

UisPerformingTask::~UisPerformingTask()
{

}

bool UisPerformingTask::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool b = false;
	if (m_owner)
	{
		b = m_owner->isCastingSkill();
	}
	return b;
}

void UisPerformingTask::SetOwner(AActor* ActorOwner)
{
	ActorOwner->GetActorLocation();
	m_owner = (ABaseCharacter*)ActorOwner;
}