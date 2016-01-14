#pragma once

#include "BaseBuffCompenent.h"
#include "Buff.generated.h"


class ABaseCharacter;
class UAISimCharacter;

template<typename T> UBaseBuffCompenent * createBcInstance(UObject* obj) { return NewObject<T>(obj); }

typedef UBaseBuffCompenent* (*bCclassFuncPtr)(UObject* obj);


UCLASS()
class  HEROBATTLE_API UBuff : public UObject
{
	GENERATED_BODY()
public:
	UBuff();
	~UBuff();

	void init(ABaseCharacter* owner, TArray<FBuffContainer> bCBuffList, float duration, FString name, FString usage, FSkillProperties properties, UBuff* ownerBuff);
	void initSim(UAISimCharacter* owner, TArray<FBuffContainer> bCBuffList, float duration, FString name, FString usage, FSkillProperties properties, UBuff* ownerBuff);

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

	static TMap<FString, bCclassFuncPtr> bcObjectNameList;

	UPROPERTY()
	TArray<UBaseBuffCompenent*> m_BcList;

	float m_Duration;
	FString m_Name;
	bool m_IsInfinityUsage;
	int32 m_Usage;
};

