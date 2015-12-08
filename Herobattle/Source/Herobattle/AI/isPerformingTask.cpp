// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "isPerformingTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIGameState.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Base/BaseCharacter.h"
#include "AIController.h"




UisPerformingTask::UisPerformingTask()
{
	bCreateNodeInstance = true;
}

UisPerformingTask::~UisPerformingTask()
{

}

bool UisPerformingTask::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool b = false;
	if (AIOwnerController->GetPawn())
	{
		ABaseCharacter* owner = (ABaseCharacter*)AIOwnerController->GetPawn();
		b = owner->isCastingSkill();
	}
	return b;
}

void UisPerformingTask::SetOwner(AActor* ActorOwner)
{
	AIOwnerController = Cast<AAIController>(ActorOwner);

}