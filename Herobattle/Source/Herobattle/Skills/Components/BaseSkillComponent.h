#pragma once

#include "../../Enum/SkillEnums.h"
#include <map>
#include "XmlParser.h"
#include "BaseSkillComponent.generated.h"



class ABaseCharacter;



UCLASS()
class  HEROBATTLE_API UBaseSkillComponent : public UObject
{
	GENERATED_BODY()
//Parameters
public:


public:
	UBaseSkillComponent();
	~UBaseSkillComponent();

	virtual bool run(ABaseCharacter* target, ABaseCharacter* self);
	virtual float getScore();
	virtual void init(FXmlNode* node);
	virtual FString ToString();

	static UBaseSkillComponent* UBaseSkillComponent::MAKE();

	FString SkillName;
	int scaleTable[20];
	Attributes scaleAttribute;

protected:
	void fillScaleTable(FXmlNode* node);
};

