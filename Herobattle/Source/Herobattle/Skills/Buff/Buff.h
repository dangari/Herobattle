#pragma once

#include "BaseBuffCompenent.h"
#include "Buff.generated.h"


class ABaseCharacter;
class UAISimCharacter;


typedef UBaseBuffCompenent* (*bCclassFuncPtr)();


UCLASS()
class  HEROBATTLE_API UBuff : public UObject
{
	GENERATED_BODY()
public:
	UBuff();
	~UBuff();

	void init(ABaseCharacter* owner, TArray<FBuffContainer> bCBuffList, float duration, FString name, FString usage, FSkillProperties properties);
	void initSim(UAISimCharacter* owner, TArray<FBuffContainer> bCBuffList, float duration, FString name, FString usage, FSkillProperties properties);

	void initDummyBuff();

	//value is incoming damage or heal
	// heal is positive and and damage is negative
	bool run(ABaseCharacter* target, ABaseCharacter* self, int value = 0);
	bool runSim(UAISimCharacter* target, UAISimCharacter* self, int value = 0);

	void updateBuff(float deltaTime);
	// test if the buff is still active
	bool isExpired();

	float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore);
	float getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore);

	//getter/setter
	FString getName();

	UBuff* copy();

	

	UPROPERTY()
	TArray<UBaseBuffCompenent*> m_BcList;

	float m_Duration;
	FString m_Name;
	bool m_IsInfinityUsage;
	int32 m_Usage;
};

