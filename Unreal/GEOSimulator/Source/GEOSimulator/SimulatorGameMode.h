// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GEORPCServer.h"
#include "SimulatorGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GEOSIMULATOR_API ASimulatorGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ASimulatorGameMode();	
	~ASimulatorGameMode();

	geocontrol::GEORPCServer* server;

	void BeginPlay() override;
};
