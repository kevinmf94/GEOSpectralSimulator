// Fill out your copyright notice in the Description page of Project Settings.

#include "GEOSimulatorAPIGameModeBase.h"
#include "DronePawn.h"
#include "CameraHUD.h"
#include "WorldManager.h"
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
	worldManager = GetWorld()->SpawnActor<AWorldManager>(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
}

AWorldManager* AGEOSimulatorAPIGameModeBase::GetWorldManager()
{
	return worldManager;
}

