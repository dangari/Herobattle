#pragma once

#include "../../Enum/SkillEnums.h"
#include <map>
#include "BaseSkillComponent.generated.h"



class ABaseCharacter;
class FXmlNode;
class UBaseSkillComponent;

typedef UBaseSkillComponent* (*pfnCreateClass)();
template<class T> UBaseSkillComponent* createT() { return new T; }

struct RegisterComponent
{
public:
	typedef std::map<std::string, UBaseSkillComponent*(*)()> map_type;

	static UBaseSkillComponent* createInstance(std::string const& s)
	{
		map_type::iterator it = getMap()->find(s);
		if (it == getMap()->end())
			return 0;
		return it->second();
	}

protected:
	static map_type * getMap()
	{
		if (!map)
		{
			map = new map_type;
		}
		return map;
	}

private:
	static map_type * map;

};

template<class T>
struct DerivedRegister : RegisterComponent {
	DerivedRegister(std::string const& s) {
		getMap()->insert(std::make_pair(s, &createT<T>));
	}
};


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

private:
	FString tagName;
	static DerivedRegister<UBaseSkillComponent> reg;
};

