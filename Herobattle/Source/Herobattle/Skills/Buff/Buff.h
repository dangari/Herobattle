#pragma once

#include "BaseBuffCompenent.h"
#include "Buff.generated.h"


class ABaseCharacter;


typedef UBaseBuffCompenent* (*bCclassFuncPtr)();


UCLASS()
class  HEROBATTLE_API UBuff : public UObject
{
	GENERATED_BODY()
public:
	UBuff();
	~UBuff();

	void init(ABaseCharacter* owner, TArray<FBuffContainer> bCBuffList, float duration, FString name, FString usage);

	//value is incoming damage or heal
	// heal is positive and and damage is negative
	bool run(ABaseCharacter* target, ABaseCharacter* self, int value);

	void updateBuff(float deltaTime);
	// test if the buff is still active
	bool isExpired();

	//getter/setter
	FString getName();

private:
	TArray<UBaseBuffCompenent*> m_BcList;

	float m_Duration;
	FString m_Name;
	bool m_IsInfinityUsage;
	int32 m_Usage;
};

