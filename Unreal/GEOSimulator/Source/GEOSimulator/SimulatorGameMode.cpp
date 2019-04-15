// Fill out your copyright notice in the Description page of Project Settings.

#include "SimulatorGameMode.h"
#include "VehiclePawn.h"
#include "CameraHUD.h"

#include "GEORPCServer.h"
using namespace geocontrol;

ASimulatorGameMode::ASimulatorGameMode()
{
	DefaultPawnClass = AVehiclePawn::StaticClass();
	HUDClass = ACameraHUD::StaticClass();
}

void ASimulatorGameMode::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Begin Play ASimulatorGameMode"));
	server = new GEORPCServer();
	server->init();
	server->bindGeoControl();
	server->run();
	UE_LOG(LogTemp, Warning, TEXT("Server started"));
}

ASimulatorGameMode::~ASimulatorGameMode()
{
	this->server->stop();
}