// Fill out your copyright notice in the Description page of Project Settings.

#include "GEOSimulatorAPIGameModeBase.h"
#include "DronePawn.h"
#include "CameraHUD.h"
#include "WorldManager.h"
#include "GameFramework/PlayerStart.h"
#include "EngineUtils.h"
#include "Engine/World.h"

AGEOSimulatorAPIGameModeBase::AGEOSimulatorAPIGameModeBase()
{
	DefaultPawnClass = ADronePawn::StaticClass();
	HUDClass = ACameraHUD::StaticClass();
}

AGEOSimulatorAPIGameModeBase::~AGEOSimulatorAPIGameModeBase()
{
}

void AGEOSimulatorAPIGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    
	worldManager = GetWorld()->SpawnActor<AWorldManager>(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
	/*AActor* actor;

	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		actor = *ActorItr;
		FString actorName = ActorItr->GetName();
		if (actorName.Contains(TEXT("BP_Sky_Sphere")))
		{
			UE_LOG(LogTemp, Warning, TEXT("ActorFor: [%s]"), *actorName);
			ActorItr->SetActorLocation(FVector(412394.118618708f, 4612149.208618707f, 0.0f));
			break;
		}
	}*/
}

/*AActor* AGEOSimulatorAPIGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	APlayerStart* playerStart = NewObject<APlayerStart>();
	playerStart->SetActorLocation(FVector(412394.118618708f, 4612149.208618707f, 1200.0f));
	return playerStart;
}*/

AWorldManager* AGEOSimulatorAPIGameModeBase::GetWorldManager()
{
	return worldManager;
}

