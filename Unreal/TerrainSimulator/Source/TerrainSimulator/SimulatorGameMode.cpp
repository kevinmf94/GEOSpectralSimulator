// Fill out your copyright notice in the Description page of Project Settings.

#include "SimulatorGameMode.h"
#include "VehiclePawn.h"
#include "CameraHUD.h"

ASimulatorGameMode::ASimulatorGameMode()
{
	DefaultPawnClass = AVehiclePawn::StaticClass();
	HUDClass = ACameraHUD::StaticClass();
}

void ASimulatorGameMode::BeginPlay()
{
	
}