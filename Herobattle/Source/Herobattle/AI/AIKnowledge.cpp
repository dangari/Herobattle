// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "AIKnowledge.h"
#include "AI/Navigation/NavigationSystem.h"
#include "EngineUtils.h"
#include "Base/BaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIGameState.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "AIController.h"




UAIKnowledge::UAIKnowledge()
{
	
	bCreateNodeInstance = true;

}

UAIKnowledge::~UAIKnowledge()
{

}

void UAIKnowledge::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	//get currente aiGameState
	// if there is no aiGameState it creates one and saves it with key: AIGameState
	FName keyName = "AIGameState";
	UAIGameState* aiGameState = (UAIGameState*)BlackboardComp->GetValue<UBlackboardKeyType_Object>(keyName);
	if (aiGameState == nullptr)
	{
		aiGameState = NewObject<UAIGameState>();
		BlackboardComp->SetValue<UBlackboardKeyType_Object>(keyName, aiGameState);
	}

	aiGameState->addDeltaTime(DeltaSeconds);
	if (!owner)
		owner = (ABaseCharacter*)AIOwnerController->GetPawn();
	if (owner && !(owner->isCastingSkill()))
	{
		aiGameState->newState(owner);

		if (m_NavSys == nullptr)
			m_NavSys = UNavigationSystem::GetCurrent(GetWorld());

		for (TActorIterator<ABaseCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			if (owner != *ActorItr)
			{
				FCharacterState characterState = ActorItr->AiExtractor(owner);
				if (fRange > characterState.airDistance)
				{
					float distance;
					FVector startVec = owner->GetActorLocation();
					m_NavSys->GetPathLength(startVec, characterState.location, distance);

					characterState.walkDistance = distance;
					aiGameState->addCharacterState(characterState);
				}
			}
		}
	}
}

void UAIKnowledge::SetOwner(AActor* ActorOwner)
{
	AIOwnerController = Cast<AAIController>(ActorOwner);
}
