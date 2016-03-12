// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "LoadImages.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API ULoadImages : public UObject
{
	GENERATED_BODY()
public:
	UTexture2D* LoadSkillImage(FString name);
};
