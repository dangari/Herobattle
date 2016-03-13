// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CapturePoint.generated.h"

UENUM(BlueprintType)
enum class CaptureState : uint8{ RED, BLUE, NEUTRAL, REDPROGRESS, BLUEPROGRESS};


UCLASS()
class HEROBATTLE_API ACapturePoint : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General")
	UCapsuleComponent* BaseCollisionComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General")
	UStaticMeshComponent* CapturePointMesh;
	

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General")
	uint8 PipGain;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General")
	float CaptureTime;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = General)
	float m_CurrentCaptureTime = 11;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = General)
	CaptureState state = CaptureState::NEUTRAL;

	// Sets default values for this actor's properties
	ACapturePoint();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
	void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

	UPROPERTY()
	uint8 m_BlueCount;

	UPROPERTY()
	uint8 m_RedCount;



	float getCaptureSpeed(uint8 pips);
};
