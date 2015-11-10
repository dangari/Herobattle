#pragma once

#include "../../Enum/SkillEnums.h"
#include <map>
#include "BaseSkillComponent.generated.h"



class ABaseCharacter;
class FXmlNode;
template<typename T>
struct RegisterComponent;
//class UBaseSkillComponent;
//
//template<typename T> UBaseSkillComponent* createT() { return NewObject<T>(); }
//typedef UBaseSkillComponent* (*classFuncPtr)();
//
//template<typename T>
//struct RegisterComponent
//{
//public:
//private:
//	static TMap<FString, classFuncPtr> map;
//public:
//
//	static TMap<FString, classFuncPtr> createList()
//	{
//		TMap<FString, classFuncPtr> TempMap;
//		TempMap.Add(TEXT("default"), &createT<UBaseSkillComponent>);
//		return TempMap;
//	}
//
//	static UBaseSkillComponent* getClass(FString s)
//	{
//		UBaseSkillComponent* test = map.Find(s);
//		return test;
//	}
//
//	RegisterComponent(FString const& s)
//	{
//		map.Add(s, &createT<T>);
//	}
//
//};




UCLASS()
class  HEROBATTLE_API UBaseSkillComponent : public UObject
{
	GENERATED_BODY()
//Parameters
public:
	int scaleTable[20];
	Attributes scaleAttribute;
private:
// Functions
public:
	UBaseSkillComponent();
	~UBaseSkillComponent();

	virtual void run(ABaseCharacter* target, ABaseCharacter* self);
	virtual float getScore();
	virtual void init(FXmlNode* node);
	static UBaseSkillComponent* UBaseSkillComponent::MAKE();

private:
	FString tagName;
	static RegisterComponent<UBaseSkillComponent> reg;
};

