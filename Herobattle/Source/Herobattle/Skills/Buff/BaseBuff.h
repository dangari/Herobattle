#pragma once

#include "BaseBuff.generated.h"

class UBaseSkillComponent;
class ABaseCharacter;

UCLASS()
class  HEROBATTLE_API UBaseBuff : public UObject
{
	GENERATED_BODY()
public:
	UBaseBuff();
	~UBaseBuff();

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

