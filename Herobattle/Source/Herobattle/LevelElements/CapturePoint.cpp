// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "CapturePoint.h"
#include "Engine.h"
#include "Base/BaseCharacter.h"
#include "HerobattleGameMode.h"
#include "UnrealNetwork.h"


// Sets default values
ACapturePoint::ACapturePoint()
	:m_BlueCount(0)
	, m_RedCount(0)
	, PipGain(1)
	, CaptureTime(11)
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

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
	if (HasAuthority())
	{
		CaptureState progressColor;
		int pips = 0;

		if (m_RedCount > m_BlueCount)
		{
			pips = m_RedCount - m_BlueCount;
			progressColor = CaptureState::REDPROGRESS;
		}
		else if (m_RedCount < m_BlueCount)
		{
			pips = m_BlueCount - m_RedCount;
			progressColor = CaptureState::BLUEPROGRESS;
		}
		else
		{
			return;
		}
		float capturePrec = getCaptureSpeed(pips) * CaptureTime * DeltaTime;
		if (progressColor == CaptureState::REDPROGRESS)
		{
			capturePrec = capturePrec * -1;
		}
		m_CurrentCaptureTime += capturePrec;
		if (m_CurrentCaptureTime >= (CaptureTime * 2))
		{
			m_CurrentCaptureTime = CaptureTime * 2;
			if (state != CaptureState::BLUE)
			{
				AHerobattleGameMode* gameMode = Cast<AHerobattleGameMode>(GetWorld()->GetAuthGameMode());
				gameMode->addShrine(PipGain, TeamColor::BLUE);
				state = CaptureState::BLUE;
			}
			
		}
		else if (m_CurrentCaptureTime <= 0)
		{
			
			m_CurrentCaptureTime = 0;
			if (state != CaptureState::RED)
			{
				AHerobattleGameMode* gameMode = Cast<AHerobattleGameMode>(GetWorld()->GetAuthGameMode());
				gameMode->addShrine(PipGain, TeamColor::RED);
				state = CaptureState::RED;
			}
			
		}
		else if ((m_CurrentCaptureTime > CaptureTime && state == CaptureState::RED) || (m_CurrentCaptureTime < CaptureTime && state == CaptureState::BLUE))
		{
			AHerobattleGameMode* gameMode = Cast<AHerobattleGameMode>(GetWorld()->GetAuthGameMode());
			if (state == CaptureState::BLUE)
			{
				gameMode->removeShrine(PipGain, TeamColor::BLUE);
			}
			else if (state == CaptureState::RED)
			{
				gameMode->removeShrine(PipGain, TeamColor::RED);
			}
			
			state = CaptureState::NEUTRAL;
		}
		
	}

}

void ACapturePoint::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		ABaseCharacter* character = Cast<ABaseCharacter>(OtherActor);
		if (character && character->ETeam == TeamColor::BLUE)
		{
			m_BlueCount++;
		}
		else
		{
			m_RedCount++;
		}
		FString outPut = TEXT("Enter Area, RedTeam: ");
		outPut.AppendInt(m_RedCount);
		outPut = outPut.Append(TEXT(" BlueTeam: "));
		outPut.AppendInt(m_BlueCount);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, outPut);
	}
	
}

void ACapturePoint::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (HasAuthority())
	{
		ABaseCharacter* character = Cast<ABaseCharacter>(OtherActor);
		if (character && character->ETeam == TeamColor::BLUE && m_BlueCount > 0)
		{
			m_BlueCount--;
		}
		else if (m_RedCount > 0)
		{
			m_RedCount--;
		}
		if (m_RedCount == 0 && m_BlueCount == 0)
		{
			switch (state)
			{
			case CaptureState::RED:
				m_CurrentCaptureTime = 0;
				break;
			case CaptureState::BLUE:
				m_CurrentCaptureTime = 2 * CaptureTime;
				break;
			case CaptureState::NEUTRAL:
				m_CurrentCaptureTime = CaptureTime;
			default:
				break;
			}
		}
		FString outPut = TEXT("Left Area, RedTeam: ");
		outPut.AppendInt(m_RedCount);
		outPut = outPut.Append(TEXT(" BlueTeam: "));
		outPut.AppendInt(m_BlueCount);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, outPut);

	}
	
}

float ACapturePoint::getCaptureSpeed(uint8 pips)
{ 
	if (pips <= 0)
	{
		return 0;
	}
		
	else
	{
		float speed = 1 / CaptureTime + (((1 / CaptureTime) * 0.1) * (pips - 1));
		return speed;
	}
}

void ACapturePoint::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACapturePoint, m_CurrentCaptureTime);
	DOREPLIFETIME(ACapturePoint, state);
}


