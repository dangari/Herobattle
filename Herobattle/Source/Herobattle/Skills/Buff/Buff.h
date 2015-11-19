#pragma once

#include "Buff.generated.h"

class UBaseSkillComponent;
class ABaseCharacter;

UCLASS()
class  HEROBATTLE_API UBuff : public UObject
{
	GENERATED_BODY()
public:
	UBuff();
	~UBuff();

	void init(TArray<UBaseSkillComponent*> scList, float duration, FString name, FString usage);
	bool run(ABaseCharacter* target, ABaseCharacter* self);
	void updateDuration(float deltaTime);
	// test if the buff is still active
	bool isExpired();

	//getter/setter
	FString getName();

private:
	TArray<UBaseSkillComponent*> m_ScList;

	float m_Duration;
	FString m_Name;
	bool m_IsInfinityUsage;
	int32 m_Usage;
};

