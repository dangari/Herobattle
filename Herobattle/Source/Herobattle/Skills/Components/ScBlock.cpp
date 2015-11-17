// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "ScBlock.h"




UScBlock::UScBlock()
{

}

UScBlock::~UScBlock()
{

}

bool UScBlock::run(ABaseCharacter* target, ABaseCharacter* self)
{
	//if (m)
	return true;
}

void UScBlock::init(FXmlNode* node)
{
	FString sUsage = node->GetAttribute(TEXT("usage"));
	if (sUsage.Equals(TEXT("INF")))
	{
		m_usage = -1;
	}
	else
	{
		m_usage = FCString::Atoi(*sUsage);
	}
	m_currentUsage = m_usage;
	TArray<FXmlNode*> propertyList = node->GetChildrenNodes();
	FString tagName = node->GetTag();
	if (tagName.Equals(TEXT("knockdown")))
	{
		fillScaleTable(node);
	}
}

float UScBlock::getScore()
{
	return 0.f;
}
