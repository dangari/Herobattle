#pragma once
#include "Components/BaseSkillComponent.h"
#include "Herobattle.h"

template<typename T> UBaseSkillComponent * createT() { return NewObject<T>(); }

struct RegisterComponent
{
public:
	typedef TMap<FString, UBaseSkillComponent*(*)()> map_type;

	static UBaseSkillComponent* createInstance(FString const& s)
	{
		UBaseSkillComponent*(*)() obj = map.Find(s);
		if (obj)
		{
			return obj;
		}
		return 0;
	}
protected:
	static map_type * getMap() 
	{
		return map;
	}

private:
	static map_type map;

};

template<typename T>
struct DerivedRegister : RegisterComponent {
	DerivedRegister(FString const& s) {
		getMap()->Add(s, &createT<T>);
	}
};
