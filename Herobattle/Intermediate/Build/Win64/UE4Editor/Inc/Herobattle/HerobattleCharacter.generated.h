// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef HEROBATTLE_HerobattleCharacter_generated_h
#error "HerobattleCharacter.generated.h already included, missing '#pragma once' in HerobattleCharacter.h"
#endif
#define HEROBATTLE_HerobattleCharacter_generated_h

#define Herobattle_Source_Herobattle_HerobattleCharacter_h_9_RPC_WRAPPERS
#define Herobattle_Source_Herobattle_HerobattleCharacter_h_9_RPC_WRAPPERS_NO_PURE_DECLS
#define Herobattle_Source_Herobattle_HerobattleCharacter_h_9_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesAHerobattleCharacter(); \
	friend HEROBATTLE_API class UClass* Z_Construct_UClass_AHerobattleCharacter(); \
	public: \
	DECLARE_CLASS(AHerobattleCharacter, ACharacter, COMPILED_IN_FLAGS(0), 0, Herobattle, NO_API) \
	DECLARE_SERIALIZER(AHerobattleCharacter) \
	/** Indicates whether the class is compiled into the engine */    enum {IsIntrinsic=COMPILED_IN_INTRINSIC}; \
	virtual UObject* _getUObject() const override { return const_cast<AHerobattleCharacter*>(this); }


#define Herobattle_Source_Herobattle_HerobattleCharacter_h_9_INCLASS \
	private: \
	static void StaticRegisterNativesAHerobattleCharacter(); \
	friend HEROBATTLE_API class UClass* Z_Construct_UClass_AHerobattleCharacter(); \
	public: \
	DECLARE_CLASS(AHerobattleCharacter, ACharacter, COMPILED_IN_FLAGS(0), 0, Herobattle, NO_API) \
	DECLARE_SERIALIZER(AHerobattleCharacter) \
	/** Indicates whether the class is compiled into the engine */    enum {IsIntrinsic=COMPILED_IN_INTRINSIC}; \
	virtual UObject* _getUObject() const override { return const_cast<AHerobattleCharacter*>(this); }


#define Herobattle_Source_Herobattle_HerobattleCharacter_h_9_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AHerobattleCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AHerobattleCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AHerobattleCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AHerobattleCharacter); \
private: \
	/** Private copy-constructor, should never be used */ \
	NO_API AHerobattleCharacter(const AHerobattleCharacter& InCopy); \
public:


#define Herobattle_Source_Herobattle_HerobattleCharacter_h_9_ENHANCED_CONSTRUCTORS \
private: \
	/** Private copy-constructor, should never be used */ \
	NO_API AHerobattleCharacter(const AHerobattleCharacter& InCopy); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AHerobattleCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AHerobattleCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AHerobattleCharacter)


#define Herobattle_Source_Herobattle_HerobattleCharacter_h_6_PROLOG
#define Herobattle_Source_Herobattle_HerobattleCharacter_h_9_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Herobattle_Source_Herobattle_HerobattleCharacter_h_9_RPC_WRAPPERS \
	Herobattle_Source_Herobattle_HerobattleCharacter_h_9_INCLASS \
	Herobattle_Source_Herobattle_HerobattleCharacter_h_9_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_POP


#define Herobattle_Source_Herobattle_HerobattleCharacter_h_9_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Herobattle_Source_Herobattle_HerobattleCharacter_h_9_RPC_WRAPPERS_NO_PURE_DECLS \
	Herobattle_Source_Herobattle_HerobattleCharacter_h_9_INCLASS_NO_PURE_DECLS \
	Herobattle_Source_Herobattle_HerobattleCharacter_h_9_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_POP


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Herobattle_Source_Herobattle_HerobattleCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
