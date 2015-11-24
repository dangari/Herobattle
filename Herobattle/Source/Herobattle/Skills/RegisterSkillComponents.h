// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UBaseSkillComponent;

template<typename T> UBaseSkillComponent* createT() { return NewObject<T>(); }
typedef UBaseSkillComponent* (*classFuncPtr)();

template<typename T>
struct RegisterComponent
{
public:
private:
	static TMap<FString, classFuncPtr> map;
public:

	static TMap<FString, classFuncPtr> createList()
	{
		TMap<FString, classFuncPtr> TempMap;
		TempMap.Add(TEXT("default"), &createT<UBaseSkillComponent>);
		return TempMap;
	}

	static UBaseSkillComponent* getClass(FString s)
	{
		classFuncPtr test = *(map.Find(s));
		if (test)
		{
			UBaseSkillComponent* sc = test();
			return sc;
		}
		return nullptr;
	}

	RegisterComponent(FString const& s)
	{
		map.Add(s, &createT<T>);
	}

};


template<typename T>
TMap<FString, classFuncPtr>  RegisterComponent<T>::map = RegisterComponent::createList();