// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "CapturePoint.h"
#include "Engine.h"


// Sets default values
ACapturePoint::ACapturePoint()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseCollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BaseUCapsuleComponent"));
	BaseCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACapturePoint::OnOverlapBegin);
	BaseCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ACapturePoint::OnOverlapEnd);

	RootComponent = BaseCollisionComponent;

	CapturePointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	CapturePointMesh->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void ACapturePoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACapturePoint::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ACapturePoint::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Entered Area"));
}

void ACapturePoint::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Left Area"));
}

