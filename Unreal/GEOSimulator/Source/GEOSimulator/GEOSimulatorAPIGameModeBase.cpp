// Fill out your copyright notice in the Description page of Project Settings.

#include "GEOSimulatorAPIGameModeBase.h"
#include "VehiclePawn.h"
#include "CameraHUD.h"
#include "GEOPlayerController.h"

AGEOSimulatorAPIGameModeBase::AGEOSimulatorAPIGameModeBase()
{
	DefaultPawnClass = AVehiclePawn::StaticClass();
	HUDClass = ACameraHUD::StaticClass();
	PlayerControllerClass = AGEOPlayerController::StaticClass();
}

AGEOSimulatorAPIGameModeBase::~AGEOSimulatorAPIGameModeBase()
{
}

void AGEOSimulatorAPIGameModeBase::BeginPlay()
{
	
}
