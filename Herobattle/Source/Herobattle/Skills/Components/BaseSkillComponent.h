#pragma once
#include "BaseSkillComponent.generated.h"


class ABaseCharacter;

UENUM(BlueprintType)
enum class Attributes : uint8{ FIRE_MAGIC, HEALING_PRAYERS, PROTECTION_PRAYERS };

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

private:
	//asdjas
};

